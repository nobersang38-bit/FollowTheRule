#pragma once
#include <vector>
#include <map>
#include "Item.h"
//�� Ŭ������ ������ �����Դϴ� �ٴڿ� ���������� �����۵� ��������
//���߿� ���� �Ŵ������� ���⿡ �ִ� �����۵� �ٴڿ� �ѷ��� �̴ϴ�
//���� : 0 ~ 99
//���� : 100 ~ 199
struct ItemsManager
{
public:
	ItemsManager();

	void DebugItemsPrint();

	template<typename Sibal>
	void asdasdasd(Sibal asd, int IDX);
private:

	std::vector<Item*> Items =
	{
		new FadedFinger
		(
			100,
			"���ٷ� �հ���",
			"�뵵�� ������ ���������� �����̴�",
			Vector::Zero(),
			1,
			"�̰Ŵ� ���� ������ ���߾�� ���� ��ȭ��Ű�°ɷ� �����"
		),
		new GlassBottle
		(
			101,
			"������",
			"���𰡸� ������ ����� �� ���� �� ����",
			Vector::Zero(),
			1,
			"�̰� �������� �ְ� ��ü������ ���� �� �־�� ������ ���� Ȯ���� �����µ� �׷��� �ֺ� ������ �� �Ҹ��� �����?"
		),
		new Document
		(
			0,
			"�������� ���� ����",
			"�� �������� ��Ģ�� ���� �ֽ��ϴ�\n�̵��� ������� �սô�\n",
			Vector::Zero(),
			"ù��° ��Ģ�Դϴ� �̰� ���� �ڵ� �ȸ�������ϱ� �ѹ� ����� ���ô�"
		),

		new Document
		(
			1,
			"�������� ���� ����2",
			"�� �������� �߰� ��Ģ�� ���� �ֽ��ϴ�\n�̵��� ������� �սô�\n",
			Vector::Zero(),
			"�̰Ŵ� �̷� �Ա����� ����°ɷ� ���� �̷� ������ �ٽ� ���� ��Ģ�� ��Ű�°ɷ� ��"
		)

	};
};

template<typename Sibal>
inline void ItemsManager::asdasdasd(Sibal asd, int IDX)
{
	if (asd)
	{
		printf("IDX %d\n", IDX);
		printf("������ ����\n%s\n\n", asd->GetDevelDescription().c_str());
		printf("���̵�\n%d\n\n", asd->GetID());
		printf("�̸�\n%s\n\n", asd->GetName().c_str());
		printf("����\n%s\n\n", asd->GetDescription().c_str());
		printf("��ġ\n%d  %d\n\n", asd->GetLocation().X, asd->GetLocation().Y);
		printf("���� ���Ƚ��\n%d\n", asd->GetEnableUseCount());
		printf("\n\n\n\n\n");
	}
}
