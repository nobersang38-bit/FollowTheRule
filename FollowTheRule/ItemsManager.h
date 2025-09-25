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
//private:

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
			"지금 이 문서를 읽고 있다면, 당신은 이유도 모른 채 혈무시에 들어온 것입니다.\n여기는 당신이 알던 세계와 닮았지만, 질서가 다릅니다.\n여기서 살아 나가려면 아래의 수칙을 반드시 지키십시오.\n수칙을 따르면 끔찍한 죽음은 대부분 피할 수 있습니다.\n\n1. 사람처럼 보이는 것과 눈을 마주치지 마십시오. 사람 흉내일 뿐입니다.\n2. 한 자리에 오래 머물지 마십시오. 벽이 당신의 체온을 기억합니다.\n3. 문손잡이에 녹슨 이빨 자국이 있으면, 그 방은 한 번만 안전합니다. 두 번째 방문은 주인이 기다립니다.\n4. 클립을 찾고 &문양의 금고를 찾으십시오 그리고 금고를 여십시오\n4-1. 금고가 열리면 안에는 빛바랜 손가락이 있습니다. 당신의 것이 아닙니다. 그래도 지니고 다니십시오.\n4-2. 금고 열기에 실패했다면 경보음이 울릴 것입니다 주변에 숨을 곳을 찾아 그들이 돌아갈때까지 숨어있으십시오\n5. 주변 모서리에 무언가가 움크리고 있는것 같다면 당장 그 장소를 떠나십시오 그것은 당신을 보고 있습니다\n6. 무언가가 뒤를 따라 오고 있는것 같다면 뒤돌지 마십시오 그것은 당신이 뒤돌기를 기다리고 있는것 입니다\n7. 복잡한 길에 들어섰다면 들어갔던 입구로 다시 나오려 하지 마십시오\n8. 출구를 찾은 것 같다면 소지품이 있는지 확인하십시오 소지품은 많을 수록 좋습니다 적극활용하십시오 행운을 빕니다",
			Vector::Zero(),
			"첫번째 수칙입니다 이거 아직 코드 안만들었으니까 한번 만들어 봅시다"
		),

		//new Document
		//(
		//	1,
		//	"누군가가 남긴 문서2",
		//	"이 아이템은 추가 수칙이 적혀 있습니다\n이따가 적어보도록 합시다\n",
		//	Vector::Zero(),
		//	"이거는 미로 입구에서 생기는걸로 가죠 미로 끝나면 다시 이전 수칙을 지키는걸로 ㄱ"
		//),
		new Item
		(
			1000,
			ItemChildren::Map,
			"지도",
			"대략적인 형태는 알아볼 수 있는 것 같다",
			 Vector::Zero(),
			INT_MAX,
			"지도"
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
