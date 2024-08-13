#pragma once
#include <ynbt/Internal/YNBTByteStream.hpp>
#include <absl/container/flat_hash_map.h>
#include <ynbt/Internal/YNBTWriterConcept.hpp>
#include <variant>
#include <functional>

namespace YNBT
{
	class EndTag;
	class ByteTag;
	class ShortTag;
	class IntTag;
	class LongTag;
	class FloatTag;
	class DoubleTag;
	class ByteArrayTag;
	class StringTag;
	class ListTag;
	class CompoundTag;
	class IntArrayTag;
	class LongArrayTag;

	enum class TagID
	{
		EndTag,
		ByteTag,
		ShortTag,
		IntTag,
		LongTag,
		FloatTag,
		DoubleTag,
		ByteArrayTag,
		StringTag,
		ListTag,
		CompoundTag,
		IntArrayTag,
		LongArrayTag
	};

	using Tag = std::variant<EndTag, ByteTag, ShortTag, IntTag, LongTag, FloatTag, DoubleTag, ByteArrayTag, StringTag, ListTag, CompoundTag, IntArrayTag, LongArrayTag>;

	static Tag TagFromId(uint8_t id);

	class EndTag
	{
	public:
		EndTag() {}
		template<NBTInterfaceImpl T>
		EndTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI8(0, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		EndTag&& Read(BinaryStream<uint8_t>& stream)
		{
			T::ReadI8(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 0;
		}
		const std::string& GetName() const
		{
			return "TAG_End";
		}
		uint8_t GetValue() const
		{
			return 0;
		}
	};
	class ByteTag
	{
	private:
		char mValue;
	public:
		ByteTag(char value = { 0 }) : mValue(value) {}

		template<NBTInterfaceImpl T>
		ByteTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI8(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ByteTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadI8(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 1;
		}
		const std::string& GetName() const
		{
			return "TAG_Byte";
		}
		char GetValue() const
		{
			return mValue;
		}

		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }
		void SetValue(decltype(mValue) value) { mValue = value; }
	};
	class ShortTag
	{
	private:
		short mValue;
	public:
		ShortTag(short value = { 0 }) : mValue(value) {}
		template<NBTInterfaceImpl T>
		ShortTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI16(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ShortTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadI16(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 2;
		}
		const std::string& GetName() const
		{
			return "TAG_Short";
		}
		short GetValue() const
		{
			return mValue;
		}
		void SetValue(decltype(mValue) value) { mValue = value; }

		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(int value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(int value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(int value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(int value) { mValue /= value; return mValue; }
		decltype(mValue) operator%=(int value) { mValue %= value; return mValue; }
		decltype(mValue) operator&=(int value) { mValue &= value; return mValue; }
		decltype(mValue) operator|=(int value) { mValue |= value; return mValue; }
		decltype(mValue) operator^=(int value) { mValue ^= value; return mValue; }
		decltype(mValue) operator<<=(int value) { mValue <<= value; return mValue; }
		decltype(mValue) operator>>=(int value) { mValue >>= value; return mValue; }
		decltype(mValue) operator+(int value) { return mValue + value; }
		decltype(mValue) operator-(int value) { return mValue - value; }
		decltype(mValue) operator*(int value) { return mValue * value; }
		decltype(mValue) operator/(int value) { return mValue / value; }
		decltype(mValue) operator%(int value) { return mValue % value; }
		decltype(mValue) operator&(int value) { return mValue & value; }
		decltype(mValue) operator|(int value) { return mValue | value; }
		decltype(mValue) operator^(int value) { return mValue ^ value; }
		decltype(mValue) operator<<(int value) { return mValue << value; }
		decltype(mValue) operator>>(int value) { return mValue >> value; }
		decltype(mValue) operator-() { return -mValue; }
		decltype(mValue) operator~() { return ~mValue; }
		bool operator==(int value) { return mValue == value; }
		bool operator!=(int value) { return mValue != value; }
		bool operator<(int value) { return mValue < value; }
		bool operator>(int value) { return mValue > value; }
		bool operator<=(int value) { return mValue <= value; }
		bool operator>=(int value) { return mValue >= value; }
		bool operator&&(int value) { return mValue && value; }
		bool operator||(int value) { return mValue || value; }
		bool operator!() { return !mValue; }
	};
	class IntTag
	{
	private:
		int mValue;
	public:
		IntTag(int value = { 0 }) : mValue(value) {}
		template<NBTInterfaceImpl T>
		IntTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		IntTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadI32(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 3;
		}
		const std::string& GetName() const
		{
			return "TAG_Int";
		}
		int GetValue() const
		{
			return mValue;
		}
		void SetValue(decltype(mValue) value) { mValue = value; }
		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(int value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(int value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(int value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(int value) { mValue /= value; return mValue; }
		decltype(mValue) operator%=(int value) { mValue %= value; return mValue; }
		decltype(mValue) operator&=(int value) { mValue &= value; return mValue; }
		decltype(mValue) operator|=(int value) { mValue |= value; return mValue; }
		decltype(mValue) operator^=(int value) { mValue ^= value; return mValue; }
		decltype(mValue) operator<<=(int value) { mValue <<= value; return mValue; }
		decltype(mValue) operator>>=(int value) { mValue >>= value; return mValue; }
		decltype(mValue) operator+(int value) { return mValue + value; }
		decltype(mValue) operator-(int value) { return mValue - value; }
		decltype(mValue) operator*(int value) { return mValue * value; }
		decltype(mValue) operator/(int value) { return mValue / value; }
		decltype(mValue) operator%(int value) { return mValue % value; }
		decltype(mValue) operator&(int value) { return mValue & value; }
		decltype(mValue) operator|(int value) { return mValue | value; }
		decltype(mValue) operator^(int value) { return mValue ^ value; }
		decltype(mValue) operator<<(int value) { return mValue << value; }
		decltype(mValue) operator>>(int value) { return mValue >> value; }
		decltype(mValue) operator-() { return -mValue; }
		decltype(mValue) operator~() { return ~mValue; }
		bool operator==(int value) { return mValue == value; }
		bool operator!=(int value) { return mValue != value; }
		bool operator<(int value) { return mValue < value; }
		bool operator>(int value) { return mValue > value; }
		bool operator<=(int value) { return mValue <= value; }
		bool operator>=(int value) { return mValue >= value; }
		bool operator&&(int value) { return mValue && value; }
		bool operator||(int value) { return mValue || value; }
		bool operator!() { return !mValue; }

	};
	class LongTag
	{
	private:
		long long mValue;
	public:
		LongTag(long long value = { 0 }) : mValue(value) {}
		template<NBTInterfaceImpl T>
		LongTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI64(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		LongTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadI64(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 4;
		}
		const std::string& GetName() const
		{
			return "TAG_Long";
		}
		long long GetValue() const
		{
			return mValue;
		}
		void SetValue(decltype(mValue) value) { mValue = value; }
		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(int value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(int value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(int value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(int value) { mValue /= value; return mValue; }
		decltype(mValue) operator%=(int value) { mValue %= value; return mValue; }
		decltype(mValue) operator&=(int value) { mValue &= value; return mValue; }
		decltype(mValue) operator|=(int value) { mValue |= value; return mValue; }
		decltype(mValue) operator^=(int value) { mValue ^= value; return mValue; }
		decltype(mValue) operator<<=(int value) { mValue <<= value; return mValue; }
		decltype(mValue) operator>>=(int value) { mValue >>= value; return mValue; }
		decltype(mValue) operator+(int value) { return mValue + value; }
		decltype(mValue) operator-(int value) { return mValue - value; }
		decltype(mValue) operator*(int value) { return mValue * value; }
		decltype(mValue) operator/(int value) { return mValue / value; }
		decltype(mValue) operator%(int value) { return mValue % value; }
		decltype(mValue) operator&(int value) { return mValue & value; }
		decltype(mValue) operator|(int value) { return mValue | value; }
		decltype(mValue) operator^(int value) { return mValue ^ value; }
		decltype(mValue) operator<<(int value) { return mValue << value; }
		decltype(mValue) operator>>(int value) { return mValue >> value; }
		decltype(mValue) operator-() { return -mValue; }
		decltype(mValue) operator~() { return ~mValue; }
		bool operator==(int value) { return mValue == value; }
		bool operator!=(int value) { return mValue != value; }
		bool operator<(int value) { return mValue < value; }
		bool operator>(int value) { return mValue > value; }
		bool operator<=(int value) { return mValue <= value; }
		bool operator>=(int value) { return mValue >= value; }
		bool operator&&(int value) { return mValue && value; }
		bool operator||(int value) { return mValue || value; }
		bool operator!() { return !mValue; }
	};
	class FloatTag
	{
	private:
		float mValue;
	public:
		FloatTag(float value = { 0 }) : mValue(value) {}
		template<NBTInterfaceImpl T>
		FloatTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteF32(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		FloatTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadF32(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 5;
		}
		const std::string& GetName() const
		{
			return "TAG_Float";
		}
		float GetValue() const
		{
			return mValue;
		}
		void SetValue(decltype(mValue) value) { mValue = value; }
		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(int value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(int value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(int value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(int value) { mValue /= value; return mValue; }
		decltype(mValue) operator+(int value) { return mValue + value; }
		decltype(mValue) operator-(int value) { return mValue - value; }
		decltype(mValue) operator*(int value) { return mValue * value; }
		decltype(mValue) operator/(int value) { return mValue / value; }
		decltype(mValue) operator-() { return -mValue; }
		bool operator==(int value) { return mValue == value; }
		bool operator!=(int value) { return mValue != value; }
		bool operator<(int value) { return mValue < value; }
		bool operator>(int value) { return mValue > value; }
		bool operator<=(int value) { return mValue <= value; }
		bool operator>=(int value) { return mValue >= value; }
		bool operator&&(int value) { return mValue && value; }
		bool operator||(int value) { return mValue || value; }
		bool operator!() { return !mValue; }
	};
	class DoubleTag
	{
	private:
		double mValue;
	public:
		DoubleTag(double value = { 0 }) : mValue(value) {}
		template<NBTInterfaceImpl T>
		DoubleTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteF64(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		DoubleTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadF64(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 6;
		}
		const std::string& GetName() const
		{
			return "TAG_Double";
		}
		double GetValue() const
		{
			return mValue;
		}
		void SetValue(decltype(mValue) value) { mValue = value; }
		decltype(mValue) operator++() { mValue++; return mValue; }
		decltype(mValue) operator++(int) { mValue++; return mValue; }

		decltype(mValue) operator--() { mValue--; return mValue; }
		decltype(mValue) operator--(int) { mValue--; return mValue; }

		decltype(mValue) operator+=(int value) { mValue += value; return mValue; }
		decltype(mValue) operator-=(int value) { mValue -= value; return mValue; }
		decltype(mValue) operator*=(int value) { mValue *= value; return mValue; }
		decltype(mValue) operator/=(int value) { mValue /= value; return mValue; }
		decltype(mValue) operator+(int value) { return mValue + value; }
		decltype(mValue) operator-(int value) { return mValue - value; }
		decltype(mValue) operator*(int value) { return mValue * value; }
		decltype(mValue) operator/(int value) { return mValue / value; }
		decltype(mValue) operator-() { return -mValue; }
		bool operator==(int value) { return mValue == value; }
		bool operator!=(int value) { return mValue != value; }
		bool operator<(int value) { return mValue < value; }
		bool operator>(int value) { return mValue > value; }
		bool operator<=(int value) { return mValue <= value; }
		bool operator>=(int value) { return mValue >= value; }
		bool operator&&(int value) { return mValue && value; }
		bool operator||(int value) { return mValue || value; }
		bool operator!() { return !mValue; }
	};
	class ByteArrayTag
	{
	private:
		std::vector<char> mValue;
	public:
		ByteArrayTag(std::vector<char> value = {}) : mValue(value) {}
		template<NBTInterfaceImpl T>
		ByteArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(mValue.size(), stream);
			stream.WriteBuff(mValue);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ByteArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < mValue.size(); i++)
				mValue[i] = T::ReadI8(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 7;
		}
		const std::string& GetName() const
		{
			return "TAG_Byte_Array";
		}
		const std::vector<char>& GetValue() const
		{
			return mValue;
		}
	};
	class StringTag
	{
	private:
		std::string mValue;
	public:
		StringTag(std::string value = {}) : mValue(value) {}
		template<NBTInterfaceImpl T>
		StringTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteString(mValue, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		StringTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue = T::ReadString(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 8;
		}
		const std::string& GetName() const
		{
			return "TAG_String";
		}
		const std::string& GetValue() const
		{
			return mValue;
		}
	};
	class ListTag
	{
	private:
		std::vector<Tag> mValue;
	public:
		ListTag(const std::vector<Tag>& value = {}) : mValue(value) {}

		template<typename T>
		ListTag(const std::vector<T>& value);
		template<typename T>
		ListTag(std::vector<T>&& value);

		template<NBTInterfaceImpl T>
		ListTag&& Write(BinaryStream<uint8_t>& stream)
		{
			if (mValue.empty())
			{
				T::WriteI8(0, stream);
				T::WriteI32(0, stream);
				return std::move(*this);
			}
			std::visit([&stream](auto&& arg) { T::WriteI8(arg.GetID(), stream); }, mValue[0]);
			T::WriteI32(mValue.size(), stream);
			for (auto& tag : mValue)
				std::visit([&stream](auto&& arg) { arg.Write<T>(stream); }, tag);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		ListTag&& Read(BinaryStream<uint8_t>& stream)
		{
			uint8_t id = T::ReadI8(stream);
			size_t size = T::ReadI32(stream);
			mValue.resize(size);
			for (size_t i = 0; i < size; i++)
			{
				auto tag = TagFromId(id);
				std::visit([&stream](auto&& arg) { arg.Read<T>(stream); }, tag);
				if (id == 10)
					stream.Read(); // Skip 1 byte for the end tag
				mValue[i] = tag;
			}
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 9;
		}
		const std::string& GetName() const
		{
			return "TAG_List";
		}
		const std::vector<Tag>& GetValue() const
		{
			return mValue;
		}

		template<typename T>
		void push_back(const T& tag);
		template<typename T>
		void push_back(T&& tag);
		template<typename T>
		T& operator[](size_t index)
		{
			return std::get<T>(mValue[index]);
		}
		template<typename T>
		const T& operator[](size_t index) const
		{
			return std::get<T>(mValue[index]);
		}

		template<typename T>
		class ConversionIter;

		auto begin() const
		{
			return mValue.begin();
		}

		template<typename T>
		ConversionIter<T> begin() const
		{
			return get_converted_iter_begin<T>();
		}

		template<typename T>
		ConversionIter<T> begin()
		{
			return get_converted_iter_begin<T>();
		}


		auto end() const
		{
			return mValue.end();
		}

		template<typename T>
		auto end() const
		{
			return get_converted_iter_end<T>();
		}

		template<typename T>
		auto end()
		{
			return get_converted_iter_end<T>();
		}

		auto begin()
		{
			return mValue.begin();
		}

		auto end()
		{
			return mValue.end();
		}

		void clear()
		{
			mValue.clear();
		}

		size_t size() const
		{
			return mValue.size();
		}

		template<typename T>
		ConversionIter<T> get_converted_iter_begin()
		{
			return ConversionIter<T>(mValue.data());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_begin() const
		{
			return ConversionIter<T>(mValue.data());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_end()
		{
			return ConversionIter<T>(mValue.data() + mValue.size());
		}
		template<typename T>
		ConversionIter<T> get_converted_iter_end() const
		{
			return ConversionIter<T>(mValue.data() + mValue.size());
		}

		template<typename T>
		void for_each(const std::function<void(const T&)>& mCallback) const;

		template<typename T>
		void for_each(const std::function<void(T&)>& mCallback);

		bool holds_tag(TagID id) const;


	};
	class IntArrayTag
	{
	private:
		std::vector<int> mValue;
	public:
		IntArrayTag(std::vector<int> value = {}) : mValue(value) {}
		template<NBTInterfaceImpl T>
		IntArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(mValue.size(), stream);
			for (auto& value : mValue)
				T::WriteI32(value, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		IntArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < mValue.size(); i++)
				mValue[i] = T::ReadI32(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 9;
		}
		const std::string& GetName() const
		{
			return "TAG_List";
		}
		const std::vector<int>& GetValue() const
		{
			return mValue;
		}
	};
	class LongArrayTag
	{
	private:
		std::vector<long long> mValue;
	public:
		LongArrayTag(std::vector<long long> value = {}) : mValue(value) {}
		LongArrayTag(const LongArrayTag& other) : mValue(other.mValue) {}
		~LongArrayTag() {};
		template<NBTInterfaceImpl T>
		LongArrayTag&& Write(BinaryStream<uint8_t>& stream)
		{
			T::WriteI32(mValue.size(), stream);
			for (auto& value : mValue)
				T::WriteI64(value, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		LongArrayTag&& Read(BinaryStream<uint8_t>& stream)
		{
			mValue.resize(T::ReadI32(stream));
			for (size_t i = 0; i < mValue.size(); i++)
				mValue[i] = T::ReadI64(stream);
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 12;
		}
		const std::string& GetName() const
		{
			return "TAG_Long_Array";
		}
		const std::vector<long long>& GetValue() const
		{
			return mValue;
		}
	};
	class CompoundTag
	{
	private:
		absl::flat_hash_map<std::string, Tag> mValue;
	public:
		CompoundTag(const absl::flat_hash_map<std::string, Tag>& value = {}) : mValue(value) {}
		CompoundTag(
			const std::initializer_list<std::pair<std::string, Tag>>& value) : mValue(value) {}
		template<NBTInterfaceImpl T>
		CompoundTag&& Write(BinaryStream<uint8_t>& stream)
		{
			for (auto& [name, tag] : mValue)
			{
				T::WriteI8(tag.index(), stream);
				T::WriteString(name, stream);
				std::visit([&stream](auto&& arg) { arg.Write<T>(stream); }, tag);
			}
			T::WriteI8(0, stream);
			return std::move(*this);
		}
		template<NBTInterfaceImpl T>
		CompoundTag&& Read(BinaryStream<uint8_t>& stream)
		{
			char id = stream.Peak();
			bool isNested = false;
			while (id != 0 && isNested == false)
			{
				id = stream.Read();
				if (id == 10)
					isNested = true;
				auto name = T::ReadString(stream);
				auto tag = TagFromId(id);
				std::visit([&stream](auto&& arg) { arg.Read<T>(stream); }, tag);
				mValue[name] = tag;
				id = stream.Peak();
				if (isNested && id == 0)
				{
					stream.Read();
					id = stream.Peak();
					isNested = false;
				}
			}
			return std::move(*this);
		}
		uint8_t GetID() const
		{
			return 10;
		}
		const std::string& GetName() const
		{
			return "TAG_Compound";
		}
		const absl::flat_hash_map<std::string, Tag>& GetValue() const
		{
			return mValue;
		}

		size_t size() const
		{
			return mValue.size();
		}

		bool empty() const
		{
			return mValue.empty();
		}

		Tag& operator[](const std::string& key)
		{
			return mValue[key];
		}

		const Tag& operator[](const std::string& key) const
		{
			return mValue.at(key);
		}

		template<typename T>
		T& get(const std::string& key)
		{
			return std::get<T>(mValue[key]);
		}

		template<typename T>
		const T& get(const std::string& key) const
		{
			return std::get<T>(mValue.at(key));
		}

		template<typename T>
		void set(const std::string& key, const T& value)
		{
			mValue[key] = value;
		}
		template<typename T>
		void set(const std::string& key, T&& value)
		{
			mValue[key] = std::move(value);
		}

		auto find(const std::string& key) const
		{
			return mValue.find(key);
		}

		auto find(const std::string& key)
		{
			return mValue.find(key);
		}

		auto begin() const
		{
			return mValue.begin();
		}

		auto end() const
		{
			return mValue.end();
		}

		auto begin()
		{
			return mValue.begin();
		}

		auto end()
		{
			return mValue.end();
		}

	};

	static Tag TagFromId(uint8_t id)
	{
		switch (id)
		{
		case 0: return EndTag();
		case 1: return ByteTag();
		case 2: return ShortTag();
		case 3: return IntTag();
		case 4: return LongTag();
		case 5: return FloatTag();
		case 6: return DoubleTag();
		case 7: return ByteArrayTag();
		case 8: return StringTag();
		case 9: return ListTag();
		case 10: return CompoundTag();
		case 11: return IntArrayTag();
			/*case 12: return LongArrayTag(); */
		default: return EndTag();
		}

	}



	/*
	* DONOT MOVE THESE
	* They are here to deal with some template jank and they explode if inside the ListTag classes lol
	*/
	template<typename T>
	void ListTag::push_back(const T& tag)
	{
		if (mValue.empty())
		{
			mValue.push_back(tag);
			return;
		}
		if (mValue[0].index() != tag.GetID())
			throw std::runtime_error("Invalid tag type");
		mValue.push_back(tag);
	}

	template<typename T>
	void ListTag::push_back(T&& tag)
	{
		if (mValue.empty())
		{
			mValue.push_back(std::move(tag));
			return;
		}
		if (mValue[0].index() != tag.GetID())
			throw std::runtime_error("Invalid tag type");
		mValue.push_back(std::move(tag));
	}

	template<typename T>
	void ListTag::for_each(const std::function<void(const T&)>& mCallback) const
	{
		for (auto it = get_converted_iter_begin<T>(); it != get_converted_iter_end<T>(); ++it)
			mCallback(*it);
	}

	template<typename T>
	void ListTag::for_each(const std::function<void(T&)>& mCallback)
	{
		for (auto it = get_converted_iter_begin<T>(); it != get_converted_iter_end<T>(); ++it)
			mCallback(*it);
	}
	template<typename T>
	ListTag::ListTag(const std::vector<T>& value)
	{
		for (auto& val : value)
			mValue.push_back(val);
	}


	template<typename T>
	ListTag::ListTag(std::vector<T>&& value)
	{
		for (auto& val : value)
			mValue.push_back(std::move(val));
	}

	template<typename T>
	class ListTag::ConversionIter
	{
	public:
		ConversionIter(Tag* current) : mCurrent(current) {}

		T& operator*() {
			return std::get<T>(*mCurrent);
		}

		bool operator!=(const ListTag::ConversionIter<T>& other)
		{
			return mCurrent != other.mCurrent;
		}

		ConversionIter& operator++() {
			mCurrent++;
			return *this;
		}
	private:
		Tag* mCurrent;
	};
}