#include "ItemsManager.h"

ItemsManager::ItemsManager()
{
	//for (int i = 0; i < MapUsingItems.size(); i++)
	//{
	//	FadedFinger* FadedFING = dynamic_cast<FadedFinger*>(MapUsingItems[i]);
	//	GlassBottle* GlassBottll = dynamic_cast<GlassBottle*>(MapUsingItems[i]);
	//	if (FadedFING)
	//	{
	//		printf("IDX %d\n", i);
	//		printf("������ ����\n%s\n\n", FadedFING->GetDevelDescription().c_str());
	//		printf("���̵�\n%d\n\n", FadedFING->GetID());
	//		printf("�̸�\n%s\n\n", FadedFING->GetName().c_str());
	//		printf("����\n%s\n\n", FadedFING->GetDescription().c_str());
	//		printf("��ġ\n%d  %d\n\n", FadedFING->GetLocation().X, FadedFING->GetLocation().Y);
	//		printf("���� ���Ƚ��\n%d\n", FadedFING->GetEnableUseCount());
	//		printf("\n\n\n\n\n");
	//	}
	//	if (GlassBottll)
	//	{
	//		printf("IDX %d\n", i);
	//		printf("������ ����\n%s\n\n", GlassBottll->GetDevelDescription().c_str());
	//		printf("���̵�\n%d\n\n", GlassBottll->GetID());
	//		printf("�̸�\n%s\n\n", GlassBottll->GetName().c_str());
	//		printf("����\n%s\n\n", GlassBottll->GetDescription().c_str());
	//		printf("��ġ\n%d  %d\n\n", GlassBottll->GetLocation().X, GlassBottll->GetLocation().Y);
	//		printf("���� ���Ƚ��\n%d\n", GlassBottll->GetEnableUseCount());
	//		printf("\n\n\n\n\n");
	//	}
	//}
}

void ItemsManager::DebugItemsPrint()
{
	for (int i = 0; i < Items.size(); i++)
	{
		Item* pItem = dynamic_cast<Item*>(Items[i]);
		Document* pDocument = dynamic_cast<Document*>(Items[i]);
		//GlassBottle* pGlassBottle = dynamic_cast<GlassBottle*>(Items[i]);
		//FadedFinger* pFadedFinger = dynamic_cast<FadedFinger*>(Items[i]);

		asdasdasd(pItem, i);
		//asdasdasd(pDocument, i);
		//asdasdasd(pGlassBottle, i);
		//asdasdasd(pFadedFinger, i);
	}
}
//
//std::vector<Item> MapUsingItems =
//{
//	dynamic_cast<Item>(new FadedFinger
//	(
//		100,
//		"���ٷ� �հ���",
//		"�뵵�� ������ ���������� �����̴�",
//		Vector::Zero(),
//		1,
//		"�̰Ŵ� ���� ������ ���߾�� ���� ��ȭ��Ű�°ɷ� �����"
//	)),
//	static_cast<Item>(GlassBottle
//	(
//		101,
//		"������",
//		"���𰡸� ������ ����� �� ���� �� ����",
//		Vector::Zero(),
//		1,
//		"�̰� �������� �ְ� ��ü������ ���� �� �־�� ������ ���� Ȯ���� �����µ� �׷��� �ֺ� ������ �� �Ҹ��� �����?"
//	))
//};
////�� �� �ִ� ������(����)
//std::vector<Document> MapDocumentItems =
//{
//	Document
//	(
//		0,
//		"�������� ���� ����",
//		"�� �������� ��Ģ�� ���� �ֽ��ϴ�\n�̵��� ������� �սô�\n",
//		Vector::Zero(),
//		"ù��° ��Ģ�Դϴ� �̰� ���� �ڵ� �ȸ�������ϱ� �ѹ� ����� ���ô�"
//	),
//
//	Document
//	(
//		1,
//		"�������� ���� ����2",
//		"�� �������� �߰� ��Ģ�� ���� �ֽ��ϴ�\n�̵��� ������� �սô�\n",
//		Vector::Zero(),
//		"�̰Ŵ� �̷� �Ա����� ����°ɷ� ���� �̷� ������ �ٽ� ���� ��Ģ�� ��Ű�°ɷ� ��"
//	),
//};