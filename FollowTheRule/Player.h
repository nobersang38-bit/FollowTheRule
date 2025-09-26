#pragma once
#include<vector>
#include<map>
#include "Vector.h"
#include "ObjectsEnumClass.h"
#include "Object.h"
#include "Item.h"

//플레이어 클래스 직접 바꾸는건 자신의 위치와 UI조작
class Player : public Object
{
public:
	int Health = 10;
	int TalismanCount = 0;

	Player() = default;
	Player(const std::vector<std::vector<int64_t>>* InMap);

	void AddItem(Item InItem);
	const std::vector<Item>& GetInventory() const {
		return Inventory;
	}

	//플레이어가 움직이려면 맵이 있어야 합니다
	const std::vector<std::vector<int64_t>>* Map;
	Vector Position;

	virtual void Start() override;
	virtual void Update() override;
	float PlayerNotMoveTime = 0;
private:
	void Move();
	void Trigger();
	void ItemTrigger();
	bool IsAroundWall(Vector InCheckDirection);

	bool FindInventoryItem(std::string InName);
	std::vector<Item> Inventory;
	float MoveCoolTime = 0.0f;
	float PlayerSpeed = 0.1f;
};
