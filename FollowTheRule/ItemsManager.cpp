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
	//		printf("개발자 설명\n%s\n\n", FadedFING->GetDevelDescription().c_str());
	//		printf("아이디\n%d\n\n", FadedFING->GetID());
	//		printf("이름\n%s\n\n", FadedFING->GetName().c_str());
	//		printf("설명\n%s\n\n", FadedFING->GetDescription().c_str());
	//		printf("위치\n%d  %d\n\n", FadedFING->GetLocation().X, FadedFING->GetLocation().Y);
	//		printf("남은 사용횟수\n%d\n", FadedFING->GetEnableUseCount());
	//		printf("\n\n\n\n\n");
	//	}
	//	if (GlassBottll)
	//	{
	//		printf("IDX %d\n", i);
	//		printf("개발자 설명\n%s\n\n", GlassBottll->GetDevelDescription().c_str());
	//		printf("아이디\n%d\n\n", GlassBottll->GetID());
	//		printf("이름\n%s\n\n", GlassBottll->GetName().c_str());
	//		printf("설명\n%s\n\n", GlassBottll->GetDescription().c_str());
	//		printf("위치\n%d  %d\n\n", GlassBottll->GetLocation().X, GlassBottll->GetLocation().Y);
	//		printf("남은 사용횟수\n%d\n", GlassBottll->GetEnableUseCount());
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
//		"빛바랜 손가락",
//		"용도는 모르지만 으스러지기 직전이다",
//		Vector::Zero(),
//		1,
//		"이거는 아직 생각을 안했어요 막보 약화시키는걸로 갈까요"
//	)),
//	static_cast<Item>(GlassBottle
//	(
//		101,
//		"유리병",
//		"무언가를 담을때 사용할 수 있을 것 같다",
//		Vector::Zero(),
//		1,
//		"이거 던질수도 있고 액체같은거 담을 수 있어요 던지면 높은 확률로 깨지는데 그러면 주변 적들이 이 소리를 듣겠죠?"
//	))
//};
////볼 수 있는 아이템(문서)
//std::vector<Document> MapDocumentItems =
//{
//	Document
//	(
//		0,
//		"누군가가 남긴 문서",
//		"이 아이템은 수칙이 적혀 있습니다\n이따가 적어보도록 합시다\n",
//		Vector::Zero(),
//		"첫번째 수칙입니다 이거 아직 코드 안만들었으니까 한번 만들어 봅시다"
//	),
//
//	Document
//	(
//		1,
//		"누군가가 남긴 문서2",
//		"이 아이템은 추가 수칙이 적혀 있습니다\n이따가 적어보도록 합시다\n",
//		Vector::Zero(),
//		"이거는 미로 입구에서 생기는걸로 가죠 미로 끝나면 다시 이전 수칙을 지키는걸로 ㄱ"
//	),
//};