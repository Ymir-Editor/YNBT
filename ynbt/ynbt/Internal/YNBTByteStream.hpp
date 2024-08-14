#pragma once
#include <vector>
#include <ranges>
#include <span>
#include <type_traits>
namespace YNBT
{
	template<typename T>
	concept StreamWritable = std::is_integral_v<T> || std::is_floating_point_v<T>;

	template<typename T>
	class BinaryStream
	{
	private:
		std::vector<T> mBuffer;
		size_t mOffset;
	public:
		constexpr BinaryStream(std::vector<T> buffer = {}) : mBuffer(buffer), mOffset(0) {}
		constexpr void Skip(size_t count) { mOffset += count; }
		constexpr std::vector<T>& GetBuffer() { return mBuffer; }

		constexpr void Write(const T& value)
		{
			ResizeOnInvalidation();
			mBuffer[mOffset++] = value;
		}

		constexpr T Read()
		{
			return mBuffer[mOffset++];
		}

		template<typename U> requires StreamWritable<U>
		constexpr void Write(const U& value)
		{

			auto bytes = std::bit_cast<std::array<uint8_t , sizeof(U)>>(value);
			for (size_t i = 0; i < sizeof(U); i++)
				Write(bytes[i]);
		}

		constexpr uint8_t  Peak() const
		{
			return mBuffer[mOffset];
		}

		template<typename U> requires std::ranges::range<U>
		constexpr void WriteBuff(const U& buffer)
		{
			for (auto& value : buffer)
				Write(value);
		}


		template<typename U> requires StreamWritable<T>
		constexpr U Read()
		{
			std::array<uint8_t , sizeof(U)> bytes;
			for (size_t i = 0; i < sizeof(U); i++)
				bytes[i] = Read();
			return std::bit_cast<U>(bytes);
		}

		constexpr std::span<T> Read(size_t count)
		{
			auto span = std::span(mBuffer);
			auto result = span.subspan(mOffset, count);
			mOffset += count;
			return result;
		}
		constexpr std::span<T> ReadBuff(size_t count)
		{
			return Read(count);
		}

		constexpr void Write(const std::span<T> buffer)
		{
			for (T value : buffer)
				Write(value);
		}


		constexpr void GoTo(size_t offset) { mOffset = offset; }
		constexpr size_t GetOffset() const { return mOffset; }
	private:
		constexpr void ResizeOnInvalidation()
		{
			if (mOffset>= mBuffer.size())
				mBuffer.resize(mBuffer.size() * 2);
		}
	};
}