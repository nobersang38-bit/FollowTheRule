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
		if (!FindInventoryItem("����"))//�κ��丮�� ������ ���ٸ�
		{
			GameManager::RequestStat |= static_cast<int8_t>(Request::NoMap);
		}
		else if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleMap))
		{
			// �����ִ�
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::ToggleMap));
		}
		else
		{
			//�����ִ�
			GameManager::RequestStat |= static_cast<int8_t>(Request::ToggleMap);
		}
	}

	//�κ��丮 ���� ��û
	if (T::GetKey('i') || T::GetKey('I'))
	{
		//�̹� �����ִٸ�
		if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleInventory))
		{
			//����
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::ToggleInventory));
		}
		else
		{
			//�ѱ�
			GameManager::RequestStat |= static_cast<int8_t>(Request::ToggleInventory);
		}
	}

	//�׳� ���� ���� �� ����
	if (T::GetKey('-') || T::GetKey('_'))
	{
		//�̹� �����ִٸ�
		if (GameManager::RequestStat & static_cast<int8_t>(Request::DebugViewMap))
		{
			//����
			GameManager::RequestStat &= (~static_cast<int8_t>(Request::DebugViewMap));
		}
		else
		{
			//�ѱ�
			GameManager::RequestStat |= static_cast<int8_t>(Request::DebugViewMap);
		}
	}

	//â �� ���� ��û
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
	//������ ��� ��ư�� �����ٸ� �̰� ���� �κ��丮 â�� �����ִ��� Ȯ���ؾ� �մϴ�
	//�κ��丮 â�� �����־�� Ű�� �����ϴ�
	if (GameManager::RequestStat & static_cast<int8_t>(Request::ToggleInventory))
	{
		if (T::GetKey('1'))
		{
			//�̹� �����ִٸ�
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem1))
			{
				//����
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem1));
			}
			else
			{
				//�ѱ�
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem1);
			}
		}

		if (T::GetKey('2'))
		{
			//�̹� �����ִٸ�
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem2))
			{
				//����
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem2));
			}
			else
			{
				//�ѱ�
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem2);
			}
		}

		if (T::GetKey('3'))
		{
			//�̹� �����ִٸ�
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem3))
			{
				//����
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem3));
			}
			else
			{
				//�ѱ�
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem3);
			}
		}

		if (T::GetKey('4'))
		{
			//�̹� �����ִٸ�
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem4))
			{
				//����
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem4));
			}
			else
			{
				//�ѱ�
				GameManager::RequestStat |= static_cast<int8_t>(Request::UseItem4);
			}
		}

		if (T::GetKey('5'))
		{
			//�̹� �����ִٸ�
			if (GameManager::RequestStat & static_cast<int8_t>(Request::UseItem5))
			{
				//����
				GameManager::RequestStat &= (~static_cast<int8_t>(Request::UseItem5));
			}
			else
			{
				//�ѱ�
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




