#include "Player.h"
#include <Windows.h>
#include "Tools.h"
#include "GameManager.h"

using T = Tools;

Player::Player(const std::vector<std::vector<int>>* InMap)
{
	Map = InMap;
}

void Player::AddItem(Item InItem)
{
	Inventory.push_back(InItem);
}

bool Player::FindInventoryItem(std::string InName)
{
	bool Result = false;
	for (int i = 0; i < Inventory.size(); i++)
	{
		if (Inventory[i].GetName() == InName)
		{
			Result = true;
			break;
		}
	}
	return Result;
}

void Player::Start()
{

}

void Player::Update()
{
	Move();

	//printf("%d  %d\n", Position.X, Position.Y);
}

void Player::Move()
{
	if ((T::GetKey('w') || T::GetKey('W')) && !IsAroundWall(Vector::Down()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Down();
		MoveCoolTime = 0;
	}
	else if ((T::GetKey('s') || T::GetKey('S')) && !IsAroundWall(Vector::Up()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Up();
		MoveCoolTime = 0;
	}
	else if ((T::GetKey('a') || T::GetKey('A')) && !IsAroundWall(Vector::Left()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Left();
		MoveCoolTime = 0;
	}
	else if ((T::GetKey('d') || T::GetKey('D')) && !IsAroundWall(Vector::Right()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Right();
		MoveCoolTime = 0;
	}

	if (T::GetKey('m') || T::GetKey('M'))
	{
		if (!FindInventoryItem("지도"))//인벤토리에 지도가 없다면
		{
			GameManager::RequestStat |= static_cast<int8_t>(Request::NoMap);
		}
		else if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleMap))
		{
			// 켜져있다
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::ToggleMap));
		}
		else
		{
			//꺼져있다
			GameManager::RequestStat |= static_cast<int8_t>(Request::ToggleMap);
		}
	}

	//if (
	//	((*Map)[Position.Y][Position.X] & static_cast<int8_t>(Objects::Map)) ||
	//	((*Map)[Position.Y][Position.X] & static_cast<int8_t>(Objects::Document))
	//	)
	//{

	//}
	
	MoveCoolTime += T::DeletaTime();
}

bool Player::IsAroundWall(Vector InCheckDirection)
{
	if (((*Map)[Position.Y + InCheckDirection.Y][Position.X + InCheckDirection.X] & static_cast<int>(Objects::Wall)) != 0)
	{
		return true;
	}
	return false;
}




