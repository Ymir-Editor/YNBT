#include "YNBTFile.hpp"
#include <zlib.h>
#include <fstream>

namespace YNBT
{
	std::vector<uint8_t> NBTFile::decompress(std::span<uint8_t> data)
	{
		if (data.size()> 2)
		{
			if (data[0] == 0x1F && data[1] == 0x8B)
				return readGZip(data);
			else if (data[0] == 0x78 && (data[1] == 0x01 || data[1] == 0x9C || data[1] == 0xDA))
				return readZLib(data);
		}
		return std::vector<uint8_t>(data.begin(), data.end());
	}
	std::vector<uint8_t> NBTFile::compress(std::span<uint8_t> data)
	{
		
		switch (mCompressionType)
		{
		case YNBT::CompressionType::GZip:
		{
			std::vector<uint8_t> outBuffer;
			outBuffer.resize(data.size() + 512);
			z_stream stream;
			stream.zalloc = Z_NULL;
			stream.zfree = Z_NULL;
			stream.opaque = Z_NULL;
			stream.avail_in = data.size();
			stream.next_in = data.data();
			stream.avail_out = outBuffer.size();
			stream.next_out = outBuffer.data();

			auto ret = deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 16 + MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
			if (ret != Z_OK)
				throw std::runtime_error("Failed to initialize zlib");

			ret = deflate(&stream, Z_FINISH);
			if (ret != Z_STREAM_END)
				throw std::runtime_error("Failed to compress zlib");

			ret = deflateEnd(&stream);
			if (ret != Z_OK)
				throw std::runtime_error("Failed to end zlib");
			return outBuffer;
		}
		case YNBT::CompressionType::ZLib:
		{
			std::vector<uint8_t> outBuffer;
			outBuffer.resize(data.size() + 512);
			z_stream stream;
			stream.zalloc = Z_NULL;
			stream.zfree = Z_NULL;
			stream.opaque = Z_NULL;
			stream.avail_in = data.size();
			stream.next_in = data.data();
			stream.avail_out = outBuffer.size();
			stream.next_out = outBuffer.data();

			auto ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
			if (ret != Z_OK)
				throw std::runtime_error("Failed to initialize zlib");

			ret = deflate(&stream, Z_FINISH);
			if (ret != Z_STREAM_END)
				throw std::runtime_error("Failed to compress zlib");

			ret = deflateEnd(&stream);
			if (ret != Z_OK)
				throw std::runtime_error("Failed to end zlib");
			return outBuffer;
		}
		default:
		{
			std::vector<uint8_t> outBuffer;
			outBuffer.resize(data.size());
			for (int i = 0; i < data.size(); i++)
				outBuffer[i] = data[i];
			return outBuffer;
		}
		}
	}
	std::vector<uint8_t> NBTFile::readGZip(std::span<uint8_t> buffer)
	{
		std::vector<uint8_t> outBuffer;
		outBuffer.resize(1024 * 1024 * 5);
		z_stream stream;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;
		stream.avail_in = buffer.size();
		stream.next_in = buffer.data();
		stream.avail_out = outBuffer.size();
		stream.next_out = outBuffer.data();

		auto ret = inflateInit2(&stream, 16 + MAX_WBITS);
		if (ret != Z_OK)
			throw std::runtime_error("Failed to initialize zlib");

		ret = inflate(&stream, Z_FINISH);
		if (ret != Z_STREAM_END)
			throw std::runtime_error("Failed to decompress zlib");

		ret = inflateEnd(&stream);
		if (ret != Z_OK)
			throw std::runtime_error("Failed to end zlib");

		return outBuffer;
	}
	std::vector<uint8_t> NBTFile::readZLib(std::span<uint8_t> buffer)
	{
		std::vector<uint8_t> outBuffer;
		outBuffer.resize(1024 * 1024 * 5);
		z_stream stream;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;
		stream.avail_in = buffer.size();
		stream.next_in = buffer.data();
		stream.avail_out = outBuffer.size();
		stream.next_out = outBuffer.data();

		auto ret = inflateInit(&stream);
		if (ret != Z_OK)
			throw std::runtime_error("Failed to initialize zlib");

		ret = inflate(&stream, Z_FINISH);
		if (ret != Z_STREAM_END)
			throw std::runtime_error("Failed to decompress zlib");

		ret = inflateEnd(&stream);
		if (ret != Z_OK)
			throw std::runtime_error("Failed to end zlib");

		return outBuffer;
	}
}