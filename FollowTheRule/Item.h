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

	//�������� ���������� Ȯ���ϴ� �Լ� ���������� true
	inline const bool GetIsItemDestroy() const { return (UseCount <= 0); }

	//������ ���� ���� ȿ��
	virtual bool UsingEffect();

	Item() = default;
	Item(int InID, ItemChildren InCategory, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: ID(InID), Category(InCategory), Name(InName), Description(InDescription), Location(InLocation), UseCount(InUseCount), DevelDescription(InDevelDescription) { }
protected:
	std::string DevelDescription = "�����ڸ� ���� ����";

	int ID = 0;
	ItemChildren Category = ItemChildren::Item;
	std::string Name = "������ �̸�";
	std::string Description = "������ ����";
	Vector Location = Vector(0, 0);
	//������������ �ƴϸ� �������� ����������

	//��� ������ Ƚ��
	int UseCount = 0;
};


//���� ī�װ�
//������ ����ϸ� ������ ������ ����
//���� ������� �ʴ´�
//������ ���ٸ� ��� �����״ϱ� �׳� �̰� �迭�� ���ô�
class Document : public Item
{
public:
	Document(int InID, std::string InName, std::string InDescription, Vector InLocation, std::string InDevelDescription)
		: Item(InID, ItemChildren::Document, InName, InDescription, InLocation, INT_MAX, InDevelDescription) { }

	virtual bool UsingEffect() override;
};

//������
class GlassBottle : public Item
{
public:
	GlassBottle(int InID, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: Item(InID, ItemChildren::GlassBottle, InName, InDescription, InLocation, InUseCount, InDevelDescription) { }

	virtual bool UsingEffect() override;
};

//���ٷ� �հ���
class FadedFinger : public Item
{
public:
	FadedFinger(int InID, std::string InName, std::string InDescription, Vector InLocation, int InUseCount, std::string InDevelDescription)
		: Item(InID, ItemChildren::FadedFinger, InName, InDescription, InLocation, InUseCount, InDevelDescription) {
	}

	virtual bool UsingEffect() override;
};

//������ �� ���� �����ô�
