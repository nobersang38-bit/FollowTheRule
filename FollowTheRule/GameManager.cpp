#include <thread>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "GameManager.h"
#include "Tools.h"
#include "RythmGame.h"

using T = Tools;

float GameManager::DeltaTime = 0.0f;
char GameManager::CurrentInput = NULL;
int64_t GameManager::RequestStat = 0;

GameManager::GameManager()
{
	Initialize();
	Play();
}

void GameManager::Initialize()
{
	Map.clear();
	for (int y = 0; y < MapMain.GetMap().size(); y++)
	{
		Map.push_back(std::vector<int64_t>());
		for (int x = 0; x < MapMain.GetMap()[0].size(); x++)
		{
			Map[y].push_back(static_cast<int64_t>(MapMain.GetMap()[y][x]));
		}
	}

	PlayerMain = Player(&Map);

	bool IsPlayerPosition = false;
	for (int y = 0; y < Map.size(); y++)
	{
		for (int x = 0; x < Map[0].size(); x++)
		{
			if (Map[y][x] & static_cast<int>(Objects::Space))
			{
				PlayerMain.Position = Vector(x, y);
				Map[y][x] |= static_cast<int>(Objects::Player);
				IsPlayerPosition = true;
				break;
			}
		}
		if (IsPlayerPosition)
		{
			break;
		}
	}

	int YRandom = T::RandomRange(0, Map.size());
	int XRandom = T::RandomRange(0, Map[0].size());
	while (true)
	{
		YRandom = T::RandomRange(0, Map.size());
		XRandom = T::RandomRange(0, Map[0].size());
		if (
			(Map[YRandom][XRandom] & static_cast<int64_t>(Objects::Space)) &&
			!(Map[YRandom + 1][XRandom] & static_cast<int64_t>(Objects::Wall)) &&
			!(Map[YRandom - 1][XRandom] & static_cast<int64_t>(Objects::Wall)) &&
			!(Map[YRandom][XRandom + 1] & static_cast<int64_t>(Objects::Wall)) &&
			!(Map[YRandom][XRandom - 1] & static_cast<int64_t>(Objects::Wall))
			)
		{
			Map[YRandom][XRandom] |= static_cast<int64_t>(Objects::Map);
			break;
		}
	}

	//��Ģ ���� �δ� ��
	while (true)
	{
		YRandom = T::RandomRange(2, 6);
		if (Map[PlayerMain.Position.Y + YRandom][PlayerMain.Position.X] == static_cast<int64_t>(Objects::Space))
		{
			Map[PlayerMain.Position.Y + YRandom][PlayerMain.Position.X] |= static_cast<int64_t>(Objects::RuleDocument);
			break;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X + YRandom] == static_cast<int64_t>(Objects::Space))
		{
			Map[PlayerMain.Position.Y][PlayerMain.Position.X + YRandom] |= static_cast<int64_t>(Objects::RuleDocument);

			break;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X - YRandom] == static_cast<int64_t>(Objects::Space))
		{
			Map[PlayerMain.Position.Y][PlayerMain.Position.X - YRandom] |= static_cast<int64_t>(Objects::RuleDocument);
			break;
		}
	}

	//�� �߰� �κ�
	for (int i = 0; i < EnemyCount; i++)
	{
		while (true)
		{
			int RandomY = T::RandomRange(0, Map.size());
			int RandomX = T::RandomRange(0, Map[0].size());
			if (Map[RandomY][RandomX] == static_cast<int64_t>(Objects::Space))
			{
				Enemys.push_back(Enemy(&Map, &PlayerMain.Position, Vector(RandomX, RandomY)));
				break;
			}
		}
	}

	for (int y = Map.size() - 1; y >= 0; y--)
	{
		bool Check = false;
		for (int x = Map[0].size() - 1; x >= 0; x--)
		{
			if (Map[y][x] & static_cast<int64_t>(Objects::Space))
			{
				Map[y][x] = static_cast<int64_t>(Objects::Goal);
				Check = true;
				break;
			}
		}
		if (Check) break;
	}

	while (true)
	{
		int RandomY = T::RandomRange(0, Map.size());
		int RandomX = T::RandomRange(0, Map[0].size());
		if (Map[RandomY][RandomX] == static_cast<int64_t>(Objects::Space))
		{
			Map[RandomY][RandomX] |= static_cast<int64_t>(Objects::FadedFinger);
			break;
		}
	}

	for (int i = 0; i < TalismanCount; i++)
	{
		while (true)
		{
			int RandomY = T::RandomRange(0, Map.size());
			int RandomX = T::RandomRange(0, Map[0].size());
			if (Map[RandomY][RandomX] == static_cast<int64_t>(Objects::Space))
			{
				Map[RandomY][RandomX] |= static_cast<int64_t>(Objects::Talisman);
				break;
			}
		}
	}
}

void GameManager::Render()
{
	int StartY = (PlayerMain.Position.Y - ViewRange) >= 0 ? (PlayerMain.Position.Y - ViewRange) : 0;
	int EndY = (PlayerMain.Position.Y + ViewRange) <= Map.size() ? (PlayerMain.Position.Y + ViewRange) : Map.size();

	int StartX = (PlayerMain.Position.X - ViewRange) >= 0 ? (PlayerMain.Position.X - ViewRange) : 0;
	int EndX = (PlayerMain.Position.X + ViewRange) <= Map[0].size() ? (PlayerMain.Position.X + ViewRange) : Map[0].size();

	for (int i = 0; i < Enemys.size(); i++)
	{
		//���� ��ġ�� �����̶� �ٸ��ٸ� ���ΰ�ħ
		if (Enemys[i].Position != Enemys[i].RevertPosition)
		{
			Map[Enemys[i].RevertPosition.Y][Enemys[i].RevertPosition.X] &= (~static_cast<int64_t>(Objects::Enemy));
			Map[Enemys[i].Position.Y][Enemys[i].Position.X] |= static_cast<int64_t>(Objects::Enemy);
		}
		
	}

	Map[PlayerMain.Position.Y][PlayerMain.Position.X] |= static_cast<int64_t>(Objects::Player);
	AroundDeleteObject(PlayerMain.Position, Objects::Player);
	std::string RenderSTR = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	if (RequestStat & static_cast<int64_t>(Request::DebugViewMap))
	{
		DescripSTR = " Ctrl + ���콺 �� �Ʒ��� ����ϸ� ���������� ���Դϴ�";
		DescripsSTRTime = 1;
		//�� �Ѿ� �մϴ�
		for (int y = 0; y < Map.size(); y++)
		{
			for (int x = 0; x < Map[0].size(); x++)
			{
				if (y == 0 || y == Map.size() - 1 || x == 0 || x == Map[0].size() - 1)
				{
					RenderSTR += "X ";
				}
				//�켱������� ���ô�
				else if (Map[y][x] & static_cast<int>(Objects::Goal))
				{
					RenderSTR += "G ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Enemy))
				{
					RenderSTR += "��";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Player))
				{
					RenderSTR += "��";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Talisman))
				{
					RenderSTR += "& ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Map))
				{
					RenderSTR += "M ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::RuleDocument))
				{
					RenderSTR += "@ ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::FadedFinger))
				{
					RenderSTR += "( ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Space))
				{
					RenderSTR += "  ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Wall))
				{
					RenderSTR += "# ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Empty))
				{
					RenderSTR += "# ";
				}
			}
			RenderSTR += "\n";
		}
	}
	else if ((RequestStat & static_cast<int64_t>(Request::UseItem1)))
	{
		if (PlayerMain.GetInventory().size() <= 0)
		{
			DescripSTR += "�� ������";
			RequestStat &= (~static_cast<int64_t>(Request::UseItem1));
			DescripsSTRTime = 0;
		}
		else
		{
			RenderSTR += PlayerMain.GetInventory()[0].GetDescription().c_str();
		}
	}
	else if ((RequestStat & static_cast<int64_t>(Request::UseItem2)))
	{
		if (PlayerMain.GetInventory().size() <= 1)
		{
			DescripSTR += "�� ������";
			RequestStat &= (~static_cast<int64_t>(Request::UseItem2));
			DescripsSTRTime = 0;
		}
		else
		{
			RenderSTR += PlayerMain.GetInventory()[1].GetDescription().c_str();
		}
	}
	else if ((RequestStat & static_cast<int64_t>(Request::UseItem3)))
	{
		if (PlayerMain.GetInventory().size() <= 2)
		{
			DescripSTR += "�� ������";
			RequestStat &= (~static_cast<int64_t>(Request::UseItem3));
			DescripsSTRTime = 0;
		}
		else
		{
			RenderSTR += PlayerMain.GetInventory()[2].GetDescription().c_str();
		}
	}
	else if ((RequestStat & static_cast<int64_t>(Request::UseItem4)))
	{
		if (PlayerMain.GetInventory().size() <= 3)
		{
			DescripSTR += "�� ������";
			RequestStat &= (~static_cast<int64_t>(Request::UseItem4));
			DescripsSTRTime = 0;
		}
		else
		{
			RenderSTR += PlayerMain.GetInventory()[3].GetDescription().c_str();
		}
	}
	else if ((RequestStat & static_cast<int64_t>(Request::UseItem5)))
	{
		if (PlayerMain.GetInventory().size() <= 4)
		{
			DescripSTR += "�� ������";
			RequestStat &= (~static_cast<int64_t>(Request::UseItem5));
			DescripsSTRTime = 0;
		}
		else
		{
			RenderSTR += PlayerMain.GetInventory()[4].GetDescription().c_str();
		}
	}
	else if (RequestStat & static_cast<int64_t>(Request::ToggleInventory))
	{
		RenderSTR += "����ǰ\n";
		RenderSTR +="�ش��ϴ� ���ڸ� ���� ���� ����\n\n";
		PlayerMain.PlayerNotMoveTime = 0;
		//�κ��丮����
		for (int i = 0; i < PlayerMain.GetInventory().size(); i++)
		{
			RenderSTR += std::to_string(i + 1).c_str();
			RenderSTR += ". ";
			RenderSTR += PlayerMain.GetInventory()[i].GetName().c_str();
			RenderSTR += "\n";
		}
	}
	else if (RequestStat & static_cast<int64_t>(Request::ToggleMap) && !(RequestStat & static_cast<int64_t>(Request::NoMap)))
	{
		DescripSTR = " Ctrl + ���콺 �� �Ʒ��� ����ϸ� ���������� ���Դϴ�";
		DescripsSTRTime = 1;
		//�� �Ѿ� �մϴ�
		for (int y = 0; y < Map.size(); y++)
		{
			for (int x = 0; x < Map[0].size(); x++)
			{
				if (y == 0 || y == Map.size() - 1 || x == 0 || x == Map[0].size()-1)
				{
					RenderSTR += "X ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Space))
				{
					RenderSTR += "  ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Wall))
				{
					RenderSTR += "# ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Empty))
				{
					RenderSTR += "# ";
				}
			}
			RenderSTR += "\n";
		}
	}
	else
	{
		for (int y = StartY; y < EndY; y++)
		{
			for (int x = StartX; x <= EndX; x++)
			{
				if (y == StartY || y == EndY - 1 || x == StartX || x == EndX)
				{
					RenderSTR += "X ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Goal))
				{
					RenderSTR += "G ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Enemy))
				{
					RenderSTR += "��";
				}
				//�켱������� ���ô�
				else if (Map[y][x] & static_cast<int>(Objects::Player))
				{
					RenderSTR += "��";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Talisman))
				{
					RenderSTR += "& ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Map))
				{
					RenderSTR += "M ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::FadedFinger))
				{
					RenderSTR += "( ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::RuleDocument))
				{
					RenderSTR += "@ ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Space))
				{
					RenderSTR += "  ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Wall))
				{
					RenderSTR += "# ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Empty))
				{
					RenderSTR += "# ";
				}
			}
			RenderSTR += "\n";
		}
	}
	if (RequestStat & static_cast<int64_t>(Request::NoMap))
	{
			DescripSTR = "  ������ ������ ���� �ʽ��ϴ�";
			RequestStat &= (~static_cast<int64_t>(Request::NoMap));
			DescripsSTRTime = 0;
	}
	RenderSTR += "\n\n\nü��: ";
	for (int i = 0; i < PlayerMain.Health; i++)
	{
		RenderSTR += "��";
	}
	RenderSTR += "\n Ż������ ���� : ";
	RenderSTR += std::to_string(PlayerMain.TalismanCount).c_str();
	RenderSTR += "\n\n                         |";
	RenderSTR += DescripSTR;
	RenderSTR += "\n[����Ű:W, A, S, D]      | \n[��:M]                   | \n[�κ��丮:I]             |";
	//system("cls");
	printf("%s", RenderSTR.c_str());
}

void GameManager::AroundDeleteObject(Vector InLocation, Objects InObject)
{
	Map[InLocation.Y + 1][InLocation.X] &= (~static_cast<int>(InObject));
	Map[InLocation.Y - 1][InLocation.X] &= (~static_cast<int>(InObject));
	Map[InLocation.Y][InLocation.X + 1] &= (~static_cast<int>(InObject));
	Map[InLocation.Y][InLocation.X - 1] &= (~static_cast<int>(InObject));
}

void GameManager::LongTimeNotMove()
{
	if (PlayerMain.PlayerNotMoveTime > NotMoveEnableTime)
	{
		const int Value = 7;
		int YMin = T::Clamp(PlayerMain.Position.Y - Value, 0, Map.size()-1);
		int YMax = T::Clamp(PlayerMain.Position.Y + Value, 0, Map.size()-1);
		
		int XMin = T::Clamp(PlayerMain.Position.X - Value, 0, Map[0].size()-1);
		int XMax = T::Clamp(PlayerMain.Position.X + Value, 0, Map[0].size()-1);

		for (int y = YMin; y <= YMax; y++)
		{
			for (int x = XMin; x <= XMax; x++)
			{
				if (y == YMin || y == YMax || x == XMin || x == XMax)
				{
					Enemys.push_back(Enemy(&Map, &PlayerMain.Position, Vector(x, y)));
				}
			}
		}
	}
}

void GameManager::PlayerInputController()
{

}

void GameManager::Play()
{
	using clock = std::chrono::steady_clock;
	auto lastTime = clock::now();

	PlayerMain.Start();
	MapMain.Start();
	for (int i = 0; i < Enemys.size(); i++)
	{
		Enemys[i].Start();
	}

	while (true)
	{
		if (_kbhit())//Ű�� �����ϴ� �κ�
		{
			GameManager::CurrentInput = _getch();
		}
		//�� �κ� ��Ÿ Ÿ�� ���ϴ� ���̷���
		auto now = clock::now();
		std::chrono::duration<float> delta = now - lastTime;
		DeltaTime = delta.count();
		lastTime = now;
		if (DescripsSTRTime > 1.5f)
		{
			DescripSTR = "";
		}
		/////////////////////////////////////////////////////////////////
		PlayerMain.Update();
		MapMain.Update();
		for (int i = 0; i < Enemys.size(); i++)
		{
			Enemys[i].Update();
		}
		if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int64_t>(Objects::Goal))
		{
			RythmGame LastGame = RythmGame(PlayerMain.Health, PlayerMain.TalismanCount);
			LastGame.Play("�ǾƳ� Ÿ��?");
			break;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int64_t>(Objects::Map))
		{
			//������ ��ġ�� ����
			PlayerMain.AddItem(*Items.Items[3]);
			Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int64_t>(Objects::Map));
			DescripSTR = " ������ ȹ���߽��ϴ�";
			DescripsSTRTime = 0;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int64_t>(Objects::RuleDocument))
		{
			//��Ģ������ ��ġ�� ����
			PlayerMain.AddItem(*Items.Items[2]);
			Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int64_t>(Objects::RuleDocument));
			DescripSTR = " ������ ȹ���߽��ϴ�";
			DescripsSTRTime = 0;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int64_t>(Objects::FadedFinger))
		{
			PlayerMain.AddItem(*Items.Items[0]);
			Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int64_t>(Objects::FadedFinger));
			DescripSTR = " ���ٷ��հ����� ȹ���߽��ϴ�";
			DescripsSTRTime = 0;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int64_t>(Objects::Talisman))
		{
			bool PlayerHandTali = false;
			for (int i = 0; i < PlayerMain.GetInventory().size(); i++)
			{
				if (PlayerMain.GetInventory()[i].GetName() == "Ż������")
				{
					PlayerHandTali = true;
					break;
				}
			}
			if (!PlayerHandTali)
			{
				PlayerMain.AddItem(*Items.Items[5]);
				Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int64_t>(Objects::Talisman));
				DescripSTR = " Ż�������� ȹ���߽��ϴ�";
				DescripsSTRTime = 0;
				PlayerMain.TalismanCount++;
			}
			else
			{
				Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int64_t>(Objects::Talisman));
				DescripSTR = " Ż�������� ȹ���߽��ϴ�";
				DescripsSTRTime = 0;
				PlayerMain.TalismanCount++;
			}
		}

		for (int i = 0; i < Enemys.size(); i++)
		{
			if (Enemys[i].Position == PlayerMain.Position && 
				DamageEnableCoolTime < DamageEnableCoollTimeMain
				)
			{
				for (int j = 0; j < PlayerMain.GetInventory().size(); j++)
				{
					if (PlayerMain.GetInventory()[j].GetName() == "���ٷ� �հ���")
					{
						Enemys[i].Position = Vector::Zero();
						Map[Enemys[i].Position.Y][Enemys[i].Position.X] &= (~static_cast<int64_t>(Objects::Enemy));
						DescripSTR += "�װ��� ���� ���߽��ϴ� ������ ������ ���Դϴ�";
						DescripsSTRTime = 0;
						//Enemys.erase(Enemys.begin() + i);
						break;
					}
				}
				PlayerMain.Health--;
				DamageEnableCoollTimeMain = 0;
				if (PlayerMain.Health <= 0)
				{
					GameExit = true;
				}
				break;
			}
		}
		DamageEnableCoollTimeMain += T::DeletaTime();
		LongTimeNotMove();
		//////////////////////////////////////////////////////////////////
		Render();
		if (GameExit)
		{
			printf("�׾����ϴ� �й�..");
			break;
		}
		DescripsSTRTime += T::DeletaTime();
		GameManager::CurrentInput = NULL;
		Sleep(1000 / Frame);
	}
}




float GameManager::DeltaTimeGameManager()
{
	return DeltaTime;
}

char GameManager::CurrentInputGameManager()
{
	return CurrentInput;
}

