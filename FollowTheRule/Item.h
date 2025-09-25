#pragma once
#include <string>
#include <climits>
#include "Vector.h"

enum class ItemChildren
{
	Item = 0,
	Document,
	GlassBottle,
	FadedFinger,
	Map
};

class Item
{
public:
	inline const int GetID() const { return ID; }
	inline const std::string GetName() const { return Name; }
	inline const std::string GetDescription() const { return Description; }
	inline const std::string GetDevelDescription() const { return DevelDescription; }
	inline const Vector GetLocation() const { return Location; }
	inline void SetLocation(Vector InLocation) { Location = InLocation; }
	inline const int GetEnableUseCount() const { return UseCount; }

	//아이템이 망가졌는지 확인하는 함수 망가졌으면 true
	inline const bool GetIsItemDestroy() const { return (UseCount <= 0); }

	//아이템 사용시 실제 효과
	virtual bool UsingEffect();

	Item() = default;
	Item(int InID, ItemChildren InCategory, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: ID(InID), Category(InCategory), Name(InName), Description(InDescription), Location(InLocation), UseCount(InUseCount), DevelDescription(InDevelDescription) { }
protected:
	std::string DevelDescription = "개발자를 위한 설명";

	int ID = 0;
	ItemChildren Category = ItemChildren::Item;
	std::string Name = "아이템 이름";
	std::string Description = "아이템 설명";
	Vector Location = Vector(0, 0);
	//사용아이템인지 아니면 문서같은 아이템인지

	//사용 가능한 횟수
	int UseCount = 0;
};


//문서 카테고리
//문서는 사용하면 문서의 설명을 본다
//사용시 사라지지 않는다
//문서는 별다른 기능 없을테니까 그냥 이거 배열로 씁시다
class Document : public Item
{
public:
	Document(int InID, std::string InName, std::string InDescription, Vector InLocation, std::string InDevelDescription)
		: Item(InID, ItemChildren::Document, InName, InDescription, InLocation, INT_MAX, InDevelDescription) { }

	virtual bool UsingEffect() override;
};

//유리병
class GlassBottle : public Item
{
public:
	GlassBottle(int InID, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: Item(InID, ItemChildren::GlassBottle, InName, InDescription, InLocation, InUseCount, InDevelDescription) { }

	virtual bool UsingEffect() override;
};

//빛바랜 손가락
class FadedFinger : public Item
{
public:
	FadedFinger(int InID, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: Item(InID, ItemChildren::FadedFinger, InName, InDescription, InLocation, InUseCount, InDevelDescription) {
	}

	virtual bool UsingEffect() override;
};

//아이템 더 많이 넣읍시다
