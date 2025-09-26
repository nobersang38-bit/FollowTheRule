#pragma once


class Object
{
public:
	//게임매니저 안에 들어가야합니다
	virtual void Update() = 0;
	virtual void Start() = 0;
};

