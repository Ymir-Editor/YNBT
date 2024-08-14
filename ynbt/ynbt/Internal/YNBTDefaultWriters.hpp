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

		static void WriteI8(int8_t  value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(value);
		}

		static void WriteI16(int16_t value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteI32(int value, BinaryStream<uint8_t>& stream)
		{
			stream.Write(SwitchEndian(value, E));
		}

		static void WriteI64(int64_t value, BinaryStream<uint8_t>& stream)
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

		static int8_t  ReadI8(BinaryStream<uint8_t>& stream)
		{
			return stream.Read<int8_t>();
		}

		static int16_t ReadI16(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<int16_t>(), E);
		}

		static int ReadI32(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<int>(), E);
		}

		static int64_t ReadI64(BinaryStream<uint8_t>& stream)
		{
			return SwitchEndian(stream.Read<int64_t>(), E);
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