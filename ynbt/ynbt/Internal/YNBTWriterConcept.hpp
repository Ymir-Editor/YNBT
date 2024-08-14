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
		{ a.WriteI8(Type(int8_t ), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI16(Type(int16_t), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI32(Type(int), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteI64(Type(int64_t), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;
		{ a.WriteString(Type(const std::string&), Type(BinaryStream<uint8_t>&)) } -> std::same_as<void>;

		{ a.ReadF32(Type(BinaryStream<uint8_t>&)) } -> std::same_as<float>;
		{ a.ReadF64(Type(BinaryStream<uint8_t>&)) } -> std::same_as<double>;
		{ a.ReadI8(Type(BinaryStream<uint8_t>&)) } -> std::same_as<int8_t>;
		{ a.ReadI16(Type(BinaryStream<uint8_t>&)) } -> std::same_as<int16_t>;
		{ a.ReadI32(Type(BinaryStream<uint8_t>&)) } -> std::same_as<int>;
		{ a.ReadI64(Type(BinaryStream<uint8_t>&)) } -> std::same_as<int64_t>;
		{ a.ReadString(Type(BinaryStream<uint8_t>&)) } -> std::same_as<std::string>;
	};
}
#undef Type