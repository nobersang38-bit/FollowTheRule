#pragma once
#include <vector>
#include "Object.h"
#include "Vector.h"
class Enemy : public Object
{
public:
	Enemy() = default;
	Enemy(const std::vector<std::vector<int64_t>>* InMap, Vector* InPlayerPosition, Vector InLocation);
	Vector Position = Vector::Zero();
	Vector RevertPosition = Vector::Zero();

	virtual void Start() override;
	//플레이어를 만나면 호밍하여 따라가는 함수
	virtual void Update() override;

private:
	Vector* PlayerPosition;
	int DetectDistance = 10;
	float Speed = 0.6f;
	float TempTime = 0;
	const std::vector<std::vector<int64_t>>* Map;

};

