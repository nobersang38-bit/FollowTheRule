#include "RythmGame.h"
#include <iostream>
#include <conio.h>
#include "Tools.h"

using namespace std;

void RythmGame::Play(std::string InGameName)
{
	const int Seed = 0;

	int NoteLength = 100;
	NoteLength = NoteLength / Tools::Clamp(PlayerTalismanCount / 3, 1, 9999);

	const int NoteNum = 4;

	const int DisplayHeight = 5;

	int CurrentY = NoteLength;
	int Score = 0;
	bool** Bar = new bool* [NoteLength];
	for (int i = 0; i < NoteLength; i++)
	{
		Bar[i] = new bool[NoteNum];
	}

	BarInitialize(Bar, NoteLength, NoteNum);
	
	while (1)
	{
		int a = time(0);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
		//printf("%d\n", a);
		printf("\n���� �ص�Ű: [%d]\n", NoteLength - Score - 10);
		printf("ü��: ");
		for (int i = 0; i < PlayerHealth; i++)
		{
			printf("��");
		}
		printf("\n");
		bool WhileCheck = DisplayOut(Bar, NoteLength, NoteNum, DisplayHeight, CurrentY);
		if (!WhileCheck)
		{
			PlayerHealth--;
			Score++;
		}
		if (PlayerHealth <= 0)
		{
			break;
		}
		Score++;
		if ((NoteLength - Score - 10) <= 0)
		{
			break;
		}
	}
	//printf("\n\n\n%d", Bar[999][0]);
	//printf("\n\n\n%d", Bar[999][1]);
	//printf("\n\n\n%d", Bar[999][2]);
	//printf("\n\n\n%d", Bar[999][3]);

	//for (int i = 0; i < NoteLength; i++)
	//{
	//	for (int j = 0; j < NoteNum; j++)
	//	{
	//		printf("%d   ", Bar[i][j]);
	//	}
	//	printf("\n");
	//}
	if (PlayerHealth >0)
	{
		printf("\nŻ�⿡ �����߽��ϴ�\n");
	}
	else
	{
		printf("\nŻ�⿡ �����߽��ϴ�\n");
	}
}

void RythmGame::BarInitialize(bool** OutBar, int NoteLength, int NoteNum)
{
	//OutBar = new bool* [NoteLength];
//for (int i = 0; i < NoteLength; i++)
//{
//	OutBar[i] = new bool[NoteNum];
//}
	for (int i = 0; i < NoteLength; i++)
	{
		for (int j = 0; j < NoteNum; j++)
		{
			OutBar[i][j] = false;
		}
		OutBar[i][rand() % NoteNum] = true;//�������� ��Ʈ ��ǥ �� �ְ�
	}
}

bool RythmGame::DisplayOut(bool** Bar, int NoteLength, int NoteNum, int DisplayHeight, int& CurrentY)
{
	for (int i = DisplayHeight + (NoteLength - CurrentY); i >= (NoteLength - CurrentY); i--)//ȭ�� ����
	{
		printf("%d  ", i);
		for (int j = 0; j < NoteNum; j++)//��Ʈ ����
		{
			if (Bar[i][j] == true)
			{
				printf("___    ");
			}
			else
			{
				printf("       ");
			}
		}
		printf("\n\n\n");
	}
	switch (InputCommand())
	{
	case 'z':
		if (Bar[(NoteLength - CurrentY)][0] == true)
		{
			CurrentY--;
			return true;
		}
		break;
	case 'x':
		if (Bar[(NoteLength - CurrentY)][1] == true)
		{
			CurrentY--;
			return true;
		}
		break;
	case '.':
		if (Bar[(NoteLength - CurrentY)][2] == true)
		{
			CurrentY--;
			return true;
		}
		break;
	case '/':
		if (Bar[(NoteLength - CurrentY)][3] == true)
		{
			CurrentY--;
			return true;
		}
		break;
	}
	return false;
}

char RythmGame::InputCommand()
{
	char Char = static_cast<char>(_getch());
	printf("%c", Char);
	return Char;
}
