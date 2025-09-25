#pragma once
#include "Player.h"
#include "Tools.h"
#include "MapGenerator.h"
#include "ItemsManager.h"
// 플레이어 몸집이 시작할때는 큰데 기믹으로 적에게 조금식 먹히면 들어갈 수 있는 구간도 만들자

enum class Request
{
	ToggleMap	= 1<<0,
	NoMap		= 2<<0,
};
class Tools;

class GameManager
{
public:
	void Play();

	GameManager();
	static int8_t RequestStat;
private:
	void Initialize();
	void Render();

	void AroundDeleteObject(Vector InLocation, Objects InObject);

	Player PlayerMain;
	MapGenerator MapMain;

	const int Frame = 30;
	const int ViewRange = 20;

	int8_t CurrentStat = 0;

	float DescripsSTRTime = 0;

	std::vector<std::vector<int>> Map;

	ItemsManager Items;

	std::string DescripSTR = "";
private:
	static float DeltaTime;
	static float DeltaTimeGameManager();

	static char CurrentInput;
	static char CurrentInputGameManager();

	friend float Tools::DeletaTime();
	friend bool Tools::GetKey(char InKey);
};

