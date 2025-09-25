#include "Item.h"

bool Item::UsingEffect()//���������� UseCount�� 1�̻��̵Ǹ� ����� ���� ���մϴ�
{
	if (GetIsItemDestroy())
	{
		return false;
	}
	UseCount--;
	return true;
}

//�� �̷��� ������ �θ�� üũ�ϰ� ����ؾ� �մϴ�
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
