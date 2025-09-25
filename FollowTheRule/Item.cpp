#include "Item.h"

bool Item::UsingEffect()//사용아이템은 UseCount가 1이상이되면 사용을 더는 못합니다
{
	if (GetIsItemDestroy())
	{
		return false;
	}
	UseCount--;
	return true;
}

//꼭 이렇게 쓰세요 부모로 체크하고 사용해야 합니다
bool Document::UsingEffect()
{
	if (!Item::UsingEffect()) return false;

	printf("%s", Description.c_str());

	return true;
}

bool GlassBottle::UsingEffect()
{
	return false;
}

bool FadedFinger::UsingEffect()
{
	return false;
}
