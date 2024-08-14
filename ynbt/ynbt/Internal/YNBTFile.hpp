#include <ynbt/Internal/YNBTTag.hpp>
#include <array>
#include <string>
#include <filesystem>
#include <fstream>
#include <span>

namespace YNBT
{
	enum class CompressionType
	{
		None,
		GZip,
		ZLib
	};

	class NBTFile
	{
	private:
		CompoundTag mRootTag{};
		std::string mRootName{};
		CompressionType mCompressionType{ CompressionType::None };
		bool mHasBedrockHeader{ false };
		constexpr static std::array<uint8_t , 11> mBedrockHeader = {
			0x0A, 0x00, 0x00, 0x00, 0xEF, 0x0A, 0x00, 0x00, 0x0A,0x00, 0x00
		};
	private:
		template<NBTInterfaceImpl T>
		void readFromSpan(std::span<uint8_t> data)
		{
			auto realData = decompress(data);
			BinaryStream<uint8_t> stream(realData);
			auto TagType = stream.Read();
			if (TagType != 0xA)
				throw std::runtime_error("Invalid NBT file");
			auto tag = StringTag{}.Read<T>(stream);
			mRootName = tag.GetValue();
			mRootTag = CompoundTag{}.Read<T>(stream);
			if (mRootTag.size() == 0 && realData.size()> 11)
			{
				stream.GoTo(11);
				mRootTag = CompoundTag{}.Read<T>(stream);
				if (mRootTag.size()> 0)
					mHasBedrockHeader = true;
			}
		}
		std::vector<uint8_t> decompress(std::span<uint8_t> data);
		std::vector<uint8_t> compress(std::span<uint8_t> data);
		template<NBTInterfaceImpl T>
		void readFromPath(const std::filesystem::path& path)
		{
			std::ifstream file(path, std::ios::binary);
			if (!file.is_open())
				throw std::runtime_error("Failed to open file");

			std::vector<uint8_t> buffer(std::filesystem::file_size(path));
			file.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
			file.close();
			readFromSpan<T>(buffer);
		}

		std::vector<uint8_t> readGZip(std::span<uint8_t> buffer);
		std::vector<uint8_t> readZLib(std::span<uint8_t> buffer);
	public:
		NBTFile() = default;
		template<NBTInterfaceImpl T>
		NBTFile(const std::filesystem::path& path)
		{
			readFromPath<T>(path);
		}
		template<NBTInterfaceImpl T>
		NBTFile(std::span<uint8_t> data)
		{
			readFromSpan<T>(data);
		}

		NBTFile(const std::string& name, const CompoundTag& tag)
		{
			mRootName = name;
			mRootTag = tag;
		}
		template<typename T>
		void ReadFromPath(const std::filesystem::path& path)
		{
			readFromPath<T>(path);
		}
		template<typename T>
		void ReadFromSpan(std::span<uint8_t> data)
		{
			readFromSpan<T>(data);
		}



		template<NBTInterfaceImpl T>
		std::vector<uint8_t> Serialize()
		{
			std::vector<uint8_t> buffer(1024 * 1024 * 5, 0x1);
			BinaryStream<uint8_t> stream(buffer);
			if (!mHasBedrockHeader)
			{
				stream.Write<uint8_t>(0xA);
				T::WriteString(mRootName, stream);
			}
			else
			{
				stream.WriteBuff(mBedrockHeader);
			}
			mRootTag.Write<T>(stream);
			stream.GetBuffer().resize(stream.GetOffset());
			return compress(stream.GetBuffer());
		}
		template<NBTInterfaceImpl T>
		void Serialize(const std::filesystem::path& path)
		{
			auto buffer = Serialize<T>();
			std::ofstream file(path, std::ios::binary);
			if (!file.is_open())
				throw std::runtime_error("Failed to open file");
			file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
			file.close();
		}
		template<typename T>
		T& Get(const std::string& key)
		{
			return mRootTag.get<T>(key);
		}
		template<typename T>
		const T& Get(const std::string& key) const
		{
			return mRootTag.get<T>(key);
		}


		auto& operator[](const std::string& key) { return mRootTag[key]; }
		auto& operator[](const std::string& key) const { return mRootTag[key]; }
		auto begin() { return mRootTag.begin(); }
		auto end() { return mRootTag.end(); }
		auto begin() const { return mRootTag.begin(); }
		auto end() const { return mRootTag.end(); }
		auto size() const { return mRootTag.size(); }
		auto empty() const { return mRootTag.empty(); }

		auto& GetRootTag() { return mRootTag; }
		auto& GetRootName() { return mRootName; }
		auto HasBedrockHeader() const{ return mHasBedrockHeader; }
		auto& GetRootTag() const { return mRootTag; }
		auto& GetRootName() const { return mRootName; }
		auto GetCompressionType() const { return mCompressionType; }

		void SetRootTag(const CompoundTag& tag) { mRootTag = tag; }
		void SetRootName(const std::string& name) { mRootName = name; }
		void SetCompressionType(CompressionType type) { mCompressionType = type; }
		void SetHasBedrockHeader(bool value) { mHasBedrockHeader = value; }



	};
};