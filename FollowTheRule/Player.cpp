#include "Player.h"
#include <Windows.h>
#include "Tools.h"
#include "GameManager.h"

using T = Tools;

Player::Player(const std::vector<std::vector<int64_t>>* InMap)
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
	Trigger();
	ItemTrigger();

	PlayerNotMoveTime += T::DeletaTime();
	//printf("%d  %d\n", Position.X, Position.Y);
}

void Player::Move()
{
	if ((T::GetKey('w') || T::GetKey('W')) && !IsAroundWall(Vector::Down()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Down();
		MoveCoolTime = 0;
		PlayerNotMoveTime = 0;
	}
	else if ((T::GetKey('s') || T::GetKey('S')) && !IsAroundWall(Vector::Up()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Up();
		MoveCoolTime = 0;
		PlayerNotMoveTime = 0;
	}
	else if ((T::GetKey('a') || T::GetKey('A')) && !IsAroundWall(Vector::Left()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Left();
		MoveCoolTime = 0;
		PlayerNotMoveTime = 0;
	}
	else if ((T::GetKey('d') || T::GetKey('D')) && !IsAroundWall(Vector::Right()) && MoveCoolTime > PlayerSpeed)
	{
		Position += Vector::Right();
		MoveCoolTime = 0;
		PlayerNotMoveTime = 0;
	}
	
	MoveCoolTime += T::DeletaTime();
}

void Player::Trigger()
{
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

	//인벤토리 열기 요청
	if (T::GetKey('i') || T::GetKey('I'))
	{
		//이미 열려있다면
		if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleInventory))
		{
			//끄기
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::ToggleInventory));
		}
		else
		{
			//켜기
			GameManager::RequestStat |= static_cast<int8_t>(Request::ToggleInventory);
		}
	}

	//그냥 조건 없이 맵 보기
	if (T::GetKey('-') || T::GetKey('_'))
	{
		//이미 열려있다면
		if (GameManager::RequestStat & static_cast<int8_t>(Request::DebugViewMap))
		{
			//끄기
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::DebugViewMap));
		}
		else
		{
			//켜기
			GameManager::RequestStat |= static_cast<int8_t>(Request::DebugViewMap);
		}
	}

	//창 다 끄기 요청
	if (T::GetKey(static_cast<char>(27)))
	{
		GameManager::RequestStat &=
			(~(
				static_cast<int8_t>(Request::ToggleMap) |
				static_cast<int8_t>(Request::ToggleInventory) |
				static_cast<int8_t>(Request::UseItem1) |
				static_cast<int8_t>(Request::UseItem2) |
				static_cast<int8_t>(Request::UseItem3) |
				static_cast<int8_t>(Request::UseItem4) |
				static_cast<int8_t>(Request::UseItem5)
				));
	}
}

void Player::ItemTrigger()
{
	//아이템 사용 버튼을 눌렀다면 이건 이제 인벤토리 창이 열려있는지 확인해야 합니다
	//인벤토리 창도 열려있어야 키가 눌립니다
	if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleInventory))
	{
		if (T::GetKey('1'))
		{
			//이미 열려있다면
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem1))
			{
				//끄기
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem1));
			}
			else
			{
				//켜기
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem1);
			}
		}

		if (T::GetKey('2'))
		{
			//이미 열려있다면
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem2))
			{
				//끄기
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem2));
			}
			else
			{
				//켜기
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem2);
			}
		}

		if (T::GetKey('3'))
		{
			//이미 열려있다면
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem3))
			{
				//끄기
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem3));
			}
			else
			{
				//켜기
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem3);
			}
		}

		if (T::GetKey('4'))
		{
			//이미 열려있다면
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem4))
			{
				//끄기
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem4));
			}
			else
			{
				//켜기
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem4);
			}
		}

		if (T::GetKey('5'))
		{
			//이미 열려있다면
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem5))
			{
				//끄기
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem5));
			}
			else
			{
				//켜기
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem5);
			}
		}
	}
	
}

bool Player::IsAroundWall(Vector InCheckDirection)
{
	if (((*Map)[Position.Y + InCheckDirection.Y][Position.X + InCheckDirection.X] & static_cast<int>(Objects::Wall)) != 0)
	{
		return true;
	}
	return false;
}




