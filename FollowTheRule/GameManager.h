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

//������ ����ϴ� Ŭ����
class GameManager
{
public:
	void Play();

	GameManager();
	//�÷��̾ ���ϰ� �ʹٰ� �� ������ ���� �˷��ش�
	static int64_t RequestStat;
private:
	void Initialize();
	//���� ��κ��� ȭ���� ����ϴ� �Լ�
	void Render();
	//�ֺ��� �����ϰ� ���� ������Ʈ�� ������ �ش���ǥ�� up down left right�� �����ش� 
	void AroundDeleteObject(Vector InLocation, Objects InObject);
	//�÷��̾ ���� �������� ������ �ߵ��ϴ� ���
	void LongTimeNotMove();

	Player PlayerMain;
	//����
	std::vector<Enemy> Enemys;
	//���� ����
	const int EnemyCount = 30;
	MapGenerator MapMain;

	//�����Ӽ���
	const int Frame = 30;
	//�÷��̾� �������� ���� ������
	const int ViewRange = 15;
	//�󸶳� �÷��̾ �� �����̸� LongTimeNotMove�Լ��� �ߵ�����
	const float NotMoveEnableTime = 10;
	int8_t CurrentStat = 0;

	//������� �� ���� �������� ���� �ʿ��� ����
	float DescripsSTRTime = 0;

	//������ ��� �ִ� ��
	std::vector<std::vector<int64_t>> Map;

	//�����س��� �����۵�
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

