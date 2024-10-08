#include <YNBT/ynbt.hpp>
#include <print>


int main()
{
	YNBT::NBTFile file{};
	std::array<uint8_t, 71> raw_hex = { 0xa, 0x0, 0x5, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0xa, 0x0, 0x14, 0x6e, 0x65, 0x73, 0x74, 0x65, 0x64, 0x20, 0x63, 0x6f, 0x6d, 0x70, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x74, 0x65, 0x73, 0x74, 0xa, 0x0, 0x3, 0x68, 0x61, 0x6d, 0x5, 0x0, 0x5, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3f, 0x40, 0x0, 0x0, 0x0, 0xa, 0x0, 0x3, 0x65, 0x67, 0x67, 0x5, 0x0, 0x5, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	file.ReadFromSpan<YNBT::JavaDisk>(raw_hex);
	auto& tag = file.GetRootTag();
	auto it = tag.find("nested compound test");
	if (it == tag.end())
	{
		std::println("No nested compound test found");
		return -1;
	}
	auto& compound = std::get<YNBT::CompoundTag>(it->second);
	auto it2 = compound.find("egg");
	if (it2 == compound.end())
	{
		std::println("No egg found");
		return -1;
	}
	it2 = compound.find("ham");
	if (it2 == compound.end())
	{
		std::println("No ham found");
		return -1;
	}
	return 0;
}