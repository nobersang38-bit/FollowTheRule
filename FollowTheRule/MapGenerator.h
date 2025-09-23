#pragma once
#include <vector>
#include "Vector.h"
//�̺�Ʈ ������Ʈ�� �÷��̾ ������ ���� �����ϴ� Ŭ����
class MapGenerator
{
public:
	MapGenerator();
	MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed);

	void DebugMapViewer();
private:
	void GeneratedMap();
	std::vector<std::vector<int>> Map;

	Vector MapsMinsize = Vector(25, 25);
	Vector MapsMaxsize = Vector(50, 50);
	int TotalSmallMaps = 10;
	int Seed = 0;
};

