#pragma once
#include <ynbt/Internal/YNBTEndianUtils.hpp>
#include <ynbt/Internal/YNBTByteStream.hpp>
#include <ynbt/Internal/YNBTWriterConcept.hpp>

namespace YNBT
{
	template<std::endian E>
	class GenericDisk
	{
	public:
		static void WriteF32(float value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteF64(double value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteI8(char value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(value);
		}

		static void WriteI16(short value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteI32(int value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteI64(long long value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteString(const std::string& value, BinaryStream<uint8_t>& stream)
		{
			WriteI16(value.size(), stream);
			if (value.size() == 0)
				return;
			stream.WriteBuff(value);
		}

		static float ReadF32(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<float>(), E);
		}

		static double ReadF64(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<double>(), E);
		}

		static char ReadI8(BinaryStream<uint8_t>& stream)
		{
			return stream.Read<char>();
		}

		static short ReadI16(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<short>(), E);
		}

		static int ReadI32(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<int>(), E);
		}

		static long long ReadI64(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<long long>(), E);
		}

		static std::string ReadString(BinaryStream<uint8_t>& stream)
		{
			auto size = ReadI16(stream);
			auto buffer = stream.Read(size);
			return std::string(buffer.begin(), buffer.end());
		}
	};
	using JavaDisk = GenericDisk<std::endian::big>;
	using BedrockDisk = GenericDisk<std::endian::little>;

	static_assert(NBTInterfaceImpl<JavaDisk>, "Java Disk Does Not Fit NBT Interface");
}