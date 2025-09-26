#pragma once
#include "Game.h"

//�ǾƳ�Ÿ�� ����� Ż�� ���
class RythmGame : public Game
{
public:
	virtual void Play(std::string InGameName) override;
	RythmGame(int InPlayerHealth, int InPlayerTalismanCount) 
		: PlayerHealth(InPlayerHealth), PlayerTalismanCount(InPlayerTalismanCount) {}
private:
	int PlayerHealth = 0;
	int PlayerTalismanCount = 0;
	void BarInitialize(bool** OutBar, int NoteLength, int NoteNum);
	bool DisplayOut(bool** Bar, int NoteLength, int NoteNum, int DisplayHeight, int& CurrentY);
	char InputCommand();
};

