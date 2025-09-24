#pragma once
#include <vector>
#include "ObjectsEnumClass.h"
#include "Vector.h"

enum class MapFilterType
{
	BackDepth = 0
};

//�̺�Ʈ ������Ʈ�� �÷��̾ ������ ���� �����ϴ� Ŭ����
//�����Ǵ� ��� �ʵ� �����մϴ�
class MapGenerator
{
public:
	MapGenerator();
	MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed);

	void DebugMapViewer();
private:
public:
	//���� ���� �����ִ� �Լ�(��� ����)
	void GenerateMap();

	/// <summary>
	/// �ΰ��� ���� �����ִ� �Լ�
	/// </summary>
	/// <param name="InMap1"></param>
	/// <param name="InMap2"></param>
	/// <param name="InMapFilterType">BackDepth�� ������ ������Ʈ�� �ڿ� ��ü�� ������ �� ó�� ���̰� ����</param>
	/// <param name="InFilterObject">����Ǵ� ������Ʈ</param>
	void MapDepthFilter(std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject);

	//��ü �ʾȿ� �ִ� ���� ���� �����ϴ� �Լ�
	std::vector<std::vector<Objects>> GenerateSmallMap(const Vector InGenerateStartLocation = Vector(0, 0));

	std::vector<std::vector<Objects>> Map;

	Vector SmallMapsMinsize = Vector(25, 25);
	Vector SmallMapsMaxsize = Vector(50, 50);

	int TotalSmallMaps = 10;
	int Seed = 0;

	//�̰Ŵ� ���� ���� ���ô� �簢�� �ϼ��ǰ� ��
	float Noise = 0.0f;
};
