#pragma once

//액터의 기본요소
//체력
//은닉정도
//시야 범위
class Object
{
public:
	//게임매니저 안에 들어가야합니다
	virtual void Update() = 0;
	virtual void Start() = 0;
};

