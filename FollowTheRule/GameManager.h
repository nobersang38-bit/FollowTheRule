#pragma once
#include "Player.h"
#include "Tools.h"
#include "MapGenerator.h"
#include "ItemsManager.h"
#include "Enemy.h"

enum class Request
{
	ToggleMap		= 1<<1,
	NoMap			= 1<<2,
	ToggleInventory	= 1<<3,
	DebugViewMap	= 1<<4,
	UseItem1		= 1<<5,
	UseItem2		= 1<<6,
	UseItem3		= 1<<7,
	UseItem4		= 1<<8,
	UseItem5		= 1<<9,
};
class Tools;

//게임을 통괄하는 클래스
class GameManager
{
public:
	void Play();

	GameManager();
	//플레이어가 뭘하고 싶다고 이 변수를 통해 알려준다
	static int64_t RequestStat;
private:
	void Initialize();
	//거의 대부분의 화면을 출력하는 함수
	void Render();
	//주변에 삭제하고 싶은 오브젝트가 있으면 해당좌표의 up down left right를 지워준다 
	void AroundDeleteObject(Vector InLocation, Objects InObject);
	//플레이어가 오래 움직이지 않으면 발동하는 기믹
	void LongTimeNotMove();

	Player PlayerMain;
	//적들
	std::vector<Enemy> Enemys;
	//적의 개수
	const int EnemyCount = 30;
	MapGenerator MapMain;

	//프레임설정
	const int Frame = 30;
	//플레이어 기준으로 보일 반지름
	const int ViewRange = 15;
	//얼마나 플레이어가 안 움직이면 LongTimeNotMove함수를 발동할지
	const float NotMoveEnableTime = 10;
	int8_t CurrentStat = 0;

	//설명란에 뜬 글이 지워지기 위해 필요한 변수
	float DescripsSTRTime = 0;

	//모든것을 담고 있는 맵
	std::vector<std::vector<int64_t>> Map;

	//저장해놓은 아이템들
	ItemsManager Items;

	int TalismanCount = 10;
	
	std::string DescripSTR = "";

	bool IsItemDescription = false;

	bool GameExit = false;

	const float DamageEnableCoolTime = 0.5f;
	float DamageEnableCoollTimeMain = 0;

	void PlayerInputController();
private:
	static float DeltaTime;
	static float DeltaTimeGameManager();

	static char CurrentInput;
	static char CurrentInputGameManager();

	friend float Tools::DeletaTime();
	friend bool Tools::GetKey(char InKey);
};

