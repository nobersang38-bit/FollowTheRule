#pragma once
#include <vector>
#include <map>
#include "Item.h"
//이 클래스는 아이템 모음입니다 바닥에 떨어져있을 아이템들 모음이죠
//나중에 게임 매니저에서 여기에 있는 아이템들 바닥에 뿌려줄 겁니다
//문서 : 0 ~ 99
//도구 : 100 ~ 199
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
			"빛바랜 손가락",
			"용도는 모르지만 으스러지기 직전이다",
			Vector::Zero(),
			1,
			"이거는 아직 생각을 안했어요 막보 약화시키는걸로 갈까요"
		),
		new GlassBottle
		(
			101,
			"유리병",
			"무언가를 담을때 사용할 수 있을 것 같다",
			Vector::Zero(),
			1,
			"이거 던질수도 있고 액체같은거 담을 수 있어요 던지면 높은 확률로 깨지는데 그러면 주변 적들이 이 소리를 듣겠죠?"
		),
		new Document
		(
			0,
			"누군가가 남긴 문서",
			"이 아이템은 수칙이 적혀 있습니다\n이따가 적어보도록 합시다\n",
			Vector::Zero(),
			"첫번째 수칙입니다 이거 아직 코드 안만들었으니까 한번 만들어 봅시다"
		),

		new Document
		(
			1,
			"누군가가 남긴 문서2",
			"이 아이템은 추가 수칙이 적혀 있습니다\n이따가 적어보도록 합시다\n",
			Vector::Zero(),
			"이거는 미로 입구에서 생기는걸로 가죠 미로 끝나면 다시 이전 수칙을 지키는걸로 ㄱ"
		)

	};
};

template<typename Sibal>
inline void ItemsManager::asdasdasd(Sibal asd, int IDX)
{
	if (asd)
	{
		printf("IDX %d\n", IDX);
		printf("개발자 설명\n%s\n\n", asd->GetDevelDescription().c_str());
		printf("아이디\n%d\n\n", asd->GetID());
		printf("이름\n%s\n\n", asd->GetName().c_str());
		printf("설명\n%s\n\n", asd->GetDescription().c_str());
		printf("위치\n%d  %d\n\n", asd->GetLocation().X, asd->GetLocation().Y);
		printf("남은 사용횟수\n%d\n", asd->GetEnableUseCount());
		printf("\n\n\n\n\n");
	}
}
