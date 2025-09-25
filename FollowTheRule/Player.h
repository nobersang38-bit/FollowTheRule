#pragma once
#include<vector>
#include<map>
#include "Vector.h"
#include "ObjectsEnumClass.h"
#include "Object.h"
#include "Item.h"

//플레이어는 일단 움직이는걸 먼저 구현합시다
class Player : public Object
{
public:
	Player() = default;
	Player(const std::vector<std::vector<int>>* InMap);

	void AddItem(Item InItem);

	//플레이어가 움직이려면 맵이 있어야 합니다
	const std::vector<std::vector<int>>* Map;
	Vector Position;

	virtual void Start() override;
	virtual void Update() override;

private:
	void Move();
	bool IsAroundWall(Vector InCheckDirection);

	bool FindInventoryItem(std::string InName);
	std::vector<Item> Inventory;

	float MoveCoolTime = 0.0f;
	float PlayerSpeed = 0.1f;
};
