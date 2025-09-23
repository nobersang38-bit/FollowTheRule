#pragma once
#include <vector>
#include "Vector.h"
//이벤트 오브젝트와 플레이어를 제외한 맵을 생성하는 클래스
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

