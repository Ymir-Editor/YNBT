#include <ynbt/ynbt.hpp>
#include <print>

int main()
{
	std::array<uint8_t, 71> raw_hex = { 0xa, 0x0, 0x5, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0xa, 0x0, 0x14, 0x6e, 0x65, 0x73, 0x74, 0x65, 0x64, 0x20, 0x63, 0x6f, 0x6d, 0x70, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x74, 0x65, 0x73, 0x74, 0xa, 0x0, 0x3, 0x68, 0x61, 0x6d, 0x5, 0x0, 0x5, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3f, 0x40, 0x0, 0x0, 0x0, 0xa, 0x0, 0x3, 0x65, 0x67, 0x67, 0x5, 0x0, 0x5, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	/*
	* The template parameter for ReadFromSpan is the Read/Write implementation to use.
	* You can define your own implementation by making a class that satisfies the NBTInterfaceImpl concept.
	* To see how to do this go look at the implementations for JavaDisk and BedrockDisk. 
	* They inherit from a base implementation that satisfies the concept and the only thing they change is the endianess.
	* Just implement the same funcs as BaseDisk with your own write/read logic.
	* By default, we have JavaDisk and BedrockDisk implementations.
	* Planned support For JavaNetwork and BedrockNetwork is a thing but in the mean time write your own lol.
	*/
	YNBT::NBTFile file{};
	file.ReadFromSpan<YNBT::JavaDisk>(raw_hex);

	// Fetches the root tag to do modifications on. You can modify through NBTFile object but it doesnt have most of the functions only reading ones.
	auto& tag = file.GetRootTag();
	// Writing a simple tag to a compound tag
	tag["intTest"] = YNBT::IntTag{ 69 }; 
	// Writing a compound tag to a compound tag with nested data
	tag["compoundTest"] = YNBT::CompoundTag{
		{"extra_goober", YNBT::IntTag{20}},
		{"another_nest", YNBT::CompoundTag{
			{"deep", YNBT::IntTag{9001}},
			{"bar", YNBT::StringTag{"hello world"}},
			{"another_anohter_nest", YNBT::CompoundTag{
				{"extra_deep", YNBT::IntTag{500}}
			}}
		}}
	};
	// Making a list tag
	YNBT::ListTag list{
		{
			YNBT::IntTag{1},
			YNBT::IntTag{2},
			YNBT::IntTag{3},
			YNBT::IntTag{4}
		}
	};
	// Adding a new element to the list
	list.push_back(YNBT::IntTag{ 5 });
	// Checking if list holds a specific type
	if (list.holds_tag(YNBT::TagID::IntTag))
		std::println("Holds INTs!!!!!!");
	// Iterate with known type using for_each
	// You may want to use for_each over the iter stuff because it looks better else they do the same thing
	list.for_each<YNBT::IntTag>([&](YNBT::IntTag& val) {val++; });
	// Iterate with known type
	for (auto it = list.get_converted_iter_begin<YNBT::IntTag>(); it != list.get_converted_iter_end<YNBT::IntTag>(); ++it)
	{
		YNBT::IntTag& val = *it;
		std::println("{}", val.GetValue()); // Expected output: 2, 3, 4, 5, 6
	}
	// Writing the list to the compound tag
	tag["our_amazing_list"] = std::move(list);
	file.Serialize<YNBT::JavaDisk>(R"(hello_world2.nbt)");
}