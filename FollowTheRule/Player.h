#pragma once
#include<vector>
#include<map>
#include "Vector.h"
#include "ObjectsEnumClass.h"
#include "Object.h"
#include "Item.h"

//�÷��̾� Ŭ���� ���� �ٲٴ°� �ڽ��� ��ġ�� UI����
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

	//�÷��̾ �����̷��� ���� �־�� �մϴ�
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
