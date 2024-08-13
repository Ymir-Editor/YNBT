#include "YNBTTag.hpp"

bool YNBT::ListTag::holds_tag(TagID id) const
{
	if (mValue.empty())
		return false;
	return std::to_underlying<TagID>(id) == mValue[0].index();
}
