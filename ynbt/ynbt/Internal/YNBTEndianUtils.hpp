#pragma once
#include <bit>

namespace YNBT
{
	template<typename T>
	using SameSizeType = std::conditional_t<sizeof(T) == 1, uint8_t , std::conditional_t<sizeof(T) == 2, uint16_t, std::conditional_t<sizeof(T) == 4, uint32_t, uint64_t>>>;

	template<typename T>
	constexpr T SwitchEndian(T val, std::endian target)
	{
		if (std::endian::native == target)
			return val;
		T result = std::bit_cast<T>(std::byteswap(std::bit_cast<SameSizeType<T>>(val)));
		return result;
	}

}