#include "MapGenerator.h"
#include "Tools.h"

using namespace Tools;

MapGenerator::MapGenerator()
{
	GenerateMap();
	DebugMapViewer();
}

MapGenerator::MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed) 
	: SmallMapsMinsize(InMapsMinSize), SmallMapsMaxsize(InMapsMaxSize), TotalSmallMaps(InTotalSmallMaps), Seed(InSeed)
{
	GenerateMap();
	DebugMapViewer();
}

void MapGenerator::DebugMapViewer()
{
	for (int i = 0; i < Map.size(); i++)
	{
		for (int j = 0; j < Map[i].size(); j++)
		{
			switch (Map[i][j])
			{
			case Objects::Space:
				printf(". ");
				break;
			case Objects::Wall:
				printf("# ");
				break;
			case Objects::Empty:
				printf("  ");
				break;
			}
		}
		printf("\n");
	}
}

void MapGenerator::GenerateMap()
{
	Map.push_back(std::vector<Objects>());
	//Map[0].push_back(Objects::)
	for (int i = 0; i < TotalSmallMaps; i++)
	{
		MapDepthFilter(Map, GenerateSmallMap(Vector(RandomRange(10, 50), RandomRange(10, 50))), Objects::Empty);
		//GenerateSmallMap(Vector(RandomRange(10, 50), RandomRange(10, 50)));
	}
}

void MapGenerator::MapDepthFilter(std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject)
{
	std::vector<std::vector<Objects>> TempMap;
	int XMax = InMap1[0].size() > InMap2[0].size() ? InMap1[0].size() : InMap2[0].size();
	int YMax = InMap1.size() > InMap2.size() ? InMap1.size() : InMap2.size();

	for (int y = 0; y < YMax; y++)
	{
		TempMap.push_back(std::vector<Objects>());
		for (int x = 0; x < XMax; x++)
		{
			TempMap[y].push_back(Objects::Empty);
		}
	}

	for (int y = 0; y < InMap1.size(); y++)
	{
		for (int x = 0; x < InMap1[0].size(); x++)
		{
			if (InMap1[y][x] != InFilterObject)
			{
				TempMap[y][x] = InMap1[y][x];
			}
		}
	}

	for (int y = 0; y < InMap2.size(); y++)
	{
		for (int x = 0; x < InMap2[0].size(); x++)
		{
			if (InMap2[y][x] != InFilterObject)
			{
				TempMap[y][x] = InMap2[y][x];
			}
		}
	}
}

std::vector<std::vector<Objects>> MapGenerator::GenerateSmallMap(const Vector InGenerateStartLocation)
{
	std::vector<std::vector<Objects>> Map;

	//맵사이즈를 랜덤으로 정합니다
	Vector MapSize = Vector(RandomRange(SmallMapsMinsize.X, SmallMapsMaxsize.X), RandomRange(SmallMapsMinsize.Y, SmallMapsMaxsize.Y));

	//맵생성 위치 만들기?
	for (int y = 0; y < InGenerateStartLocation.Y + MapSize.Y; y++)
	{
		Map.push_back(std::vector<Objects>());
		for (int x = 0; x < InGenerateStartLocation.X + MapSize.X; x++)
		{
			Map[y].push_back(Objects::Empty);
		}
	}

	//실제로 배열 생성하는 구간
	int YMin = InGenerateStartLocation.Y;
	int YMax = InGenerateStartLocation.Y + MapSize.Y;

	int XMin = InGenerateStartLocation.X;
	int XMax = InGenerateStartLocation.X + MapSize.X;

	for (int y = YMin; y < YMax; y++)
	{
		for (int x = XMin; x < XMax; x++)
		{
			if	(	
					( y == YMin || y == (YMax - 1) ) ||	//Y좌표가 처음이거나 끝부분이라면
					( x == XMin || x == (XMax - 1) )		//X좌표가 처음이거나 끝부분이라면
				)
			{
				Map[y][x] = Objects::Wall;
			}
			else //움직일 수 있는 빈공간 만들기
			{
				Map[y][x] = Objects::Space;
			}
		}
	}
	return Map;
}

