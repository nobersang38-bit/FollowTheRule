#pragma once
#include "Game.h"
class RythmGame : public Game
{
public:
	virtual void Play(std::string InGameName) override;
private:
	void BarInitialize(bool** OutBar, int NoteLength, int NoteNum);
	bool DisplayOut(bool** Bar, int NoteLength, int NoteNum, int DisplayHeight, int& CurrentY);
	char InputCommand();
};

