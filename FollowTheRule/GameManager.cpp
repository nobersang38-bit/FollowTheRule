#include <thread>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "GameManager.h"
#include "Tools.h"

using T = Tools;

float GameManager::DeltaTime = 0.0f;
char GameManager::CurrentInput = NULL;
int8_t GameManager::RequestStat = 0;

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
		Map.push_back(std::vector<int>());
		for (int x = 0; x < MapMain.GetMap()[0].size(); x++)
		{
			Map[y].push_back(static_cast<int>(MapMain.GetMap()[y][x]));
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
	while (!(Map[YRandom][XRandom] & static_cast<int8_t>(Objects::Space)))
	{
		YRandom = T::RandomRange(0, Map.size());
		XRandom = T::RandomRange(0, Map[0].size());
		if (Map[YRandom][XRandom] & static_cast<int8_t>(Objects::Space))
		{
			Map[YRandom][XRandom] |= static_cast<int8_t>(Objects::Map);
		}
	}
}

void GameManager::Render()
{
	int StartY = (PlayerMain.Position.Y - ViewRange) >= 0 ? (PlayerMain.Position.Y - ViewRange) : 0;
	int EndY = (PlayerMain.Position.Y + ViewRange) <= Map.size() ? (PlayerMain.Position.Y + ViewRange) : Map.size();

	int StartX = (PlayerMain.Position.X - ViewRange) >= 0 ? (PlayerMain.Position.X - ViewRange) : 0;
	int EndX = (PlayerMain.Position.X + ViewRange) <= Map[0].size() ? (PlayerMain.Position.X + ViewRange) : Map[0].size();

	Map[PlayerMain.Position.Y][PlayerMain.Position.X] |= static_cast<int>(Objects::Player);
	AroundDeleteObject(PlayerMain.Position, Objects::Player);
	std::string RenderSTR = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	
	if (RequestStat & static_cast<int8_t>(Request::ToggleMap) && !(RequestStat & static_cast<int8_t>(Request::NoMap)))
	{
		DescripSTR = " Ctrl + 마우스 휠 아래로 축소하면 정상적으로 보입니다";
		DescripsSTRTime = 1;
		//맵 켜야 합니다
		for (int y = 0; y < Map.size(); y++)
		{
			for (int x = 0; x < Map[0].size(); x++)
			{
				if (y == 0 || y == Map.size() - 1 || x == 0 || x == Map[0].size()-1)
				{
					RenderSTR += "X ";
					continue;
				}
				if (Map[y][x] & static_cast<int>(Objects::Space))
				{
					//printf("  ");
					RenderSTR += "  ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Wall))
				{
					//printf("■ ");
					RenderSTR += "■■";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Empty))
				{
					//printf("  ");
					RenderSTR += "■■";
				}
			}
			//if (y == EndY - 1)
			//{
			//	RenderSTR += "                                [방향키: W, A, S, D] [맵: M]";
			//}
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
					continue;
				}
				//우선순위대로 갑시다
				if (Map[y][x] & static_cast<int>(Objects::Player))
				{
					//printf("ㅅ");
					RenderSTR += "ㅊ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Map))
				{
					RenderSTR += "M ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Space))
				{
					//printf("  ");
					RenderSTR += "  ";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Wall))
				{
					//printf("■ ");
					RenderSTR += "■■";
				}
				else if (Map[y][x] & static_cast<int>(Objects::Empty))
				{
					//printf("  ");
					RenderSTR += "■■";
				}
			}
			//if (y == EndY - 1)
			//{
			//	RenderSTR += "                                [방향키: W, A, S, D] [맵: M]";
			//}
			RenderSTR += "\n";
		}
	}
	if (RequestStat & static_cast<int8_t>(Request::NoMap))
	{
			DescripSTR = "  지도를 가지고 있지 않습니다";
			RequestStat &= (~static_cast<int8_t>(Request::NoMap));
			DescripsSTRTime = 0;
	}

	RenderSTR += "\n\n\n                    |";
	RenderSTR += DescripSTR;
	RenderSTR += "\n[방향키:W, A, S, D] | \n[맵:M]              | \n[인벤토리:I]        |";
	printf("%s", RenderSTR.c_str());
}

void GameManager::AroundDeleteObject(Vector InLocation, Objects InObject)
{
	Map[InLocation.Y + 1][InLocation.X] &= (~static_cast<int>(InObject));
	Map[InLocation.Y - 1][InLocation.X] &= (~static_cast<int>(InObject));
	Map[InLocation.Y][InLocation.X + 1] &= (~static_cast<int>(InObject));
	Map[InLocation.Y][InLocation.X - 1] &= (~static_cast<int>(InObject));
}

void GameManager::Play()
{
	using clock = std::chrono::steady_clock;
	auto lastTime = clock::now();

	PlayerMain.Start();
	MapMain.Start();

	while (true)
	{
		if (_kbhit())//키를 감지하는 부분
		{
			GameManager::CurrentInput = _getch();
		}
		//이 부분 델타 타임 구하는 곳이래요
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

		if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int8_t>(Objects::Map))
		{
			PlayerMain.AddItem(*Items.Items[3]);
			Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int8_t>(Objects::Map));
			DescripSTR = " 지도를 획득했습니다";
			DescripsSTRTime = 0;
		}
		else if (Map[PlayerMain.Position.Y][PlayerMain.Position.X] & static_cast<int8_t>(Objects::Document))
		{
			PlayerMain.AddItem(*Items.Items[2]);
			Map[PlayerMain.Position.Y][PlayerMain.Position.X] &= (~static_cast<int8_t>(Objects::Document));
		}
		//////////////////////////////////////////////////////////////////
		Render();
		DescripsSTRTime += T::DeletaTime();
		GameManager::CurrentInput = NULL;
		Sleep(1000 / Frame);
		system("cls");
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

