#pragma once
#include <ynbt/Internal/YNBTByteStream.hpp>
#include <string>

#define Type(x) std::declval<x>()
namespace YNBT
{
	template<typename T>
	concept NBTInterfaceImpl = requires (T a)
	{
		{ a.WriteF32(Type(float), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteF64(Type(double), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI8(Type(char), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI16(Type(short), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI32(Type(int), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI64(Type(long long), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteString(Type(const std::string&), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;

		{ a.ReadF32(Type(BinaryStream<uint8_t>&)) } -> std::same_as<float>;
		{ a.ReadF64(Type(BinaryStream<uint8_t>&)) } -> std::same_as<double>;
		{ a.ReadI8(Type(BinaryStream<uint8_t>&)) } -> std::same_as<char>;
		{ a.ReadI16(Type(BinaryStream<uint8_t>&)) } -> std::same_as<short>;
		{ a.ReadI32(Type(BinaryStream<uint8_t>&)) } -> std::same_as<int>;
		{ a.ReadI64(Type(BinaryStream<uint8_t>&)) } -> std::same_as<long long>;
		{ a.ReadString(Type(BinaryStream<uint8_t>&)) } -> std::same_as<std::string>;
	};
}
#undef Type