#include "MapGenerator.h"
#include "Tools.h"

using namespace Tools;

MapGenerator::MapGenerator()
{
	Map = GenerateMiddleMap();
	DebugMapViewer();
}

MapGenerator::MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed) 
	: SmallMapsMinsize(InMapsMinSize), SmallMapsMaxsize(InMapsMaxSize), TotalSmallMaps(InTotalSmallMaps), Seed(InSeed)
{
	GenerateMiddleMap();
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

std::vector<std::vector<Objects>> MapGenerator::GenerateMiddleMap()
{
	std::vector<std::vector<Objects>> Temp;
	Temp.push_back(std::vector<Objects>());
	Temp[0].push_back(Objects::Empty);
	//Map[0].push_back(Objects::)
	for (int i = 0; i < TotalSmallMaps; i++)
	{
		std::vector<std::vector<Objects>> Temp2 = GenerateSmallMap(Vector(RandomRange(SmallMapsMinLocation.X, SmallMapsMaxLocation.X), RandomRange(SmallMapsMinLocation.X, SmallMapsMaxLocation.Y)));

		for (int y = 0; y < Temp2.size(); y++)
		{
			for (int x = 0; x < Temp2[0].size(); x++)
			{
				int YTemp = Clamp(y, 0, Temp.size() - 1);
				int XTemp = Clamp(x, 0, Temp[0].size() - 1);

				if (Temp2[y][x] == Objects::Wall && Temp2[y][x] == Temp[YTemp][XTemp])
				{
					printf("겹침");
					if (Direction4Object(Temp, Temp2, Objects::Wall))
					{
						i--;
						continue;
					}
				}
			}
		}

		Temp = MapDepthFilter(Temp, GenerateSmallMap(Vector(RandomRange(10, 100), RandomRange(10, 100))), Objects::Empty);
		//GenerateSmallMap(Vector(RandomRange(10, 50), RandomRange(10, 50)));
	}
	return Temp;
}

std::vector<std::vector<Objects>> MapGenerator::MapDepthFilter(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject)
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
	return TempMap;
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

std::vector<std::vector<Objects>> MapGenerator::MapLocationSet(std::vector<std::vector<Objects>>& InMap, const Vector InSetLocation)
{
	std::vector<std::vector<Objects>> Temp;

	int YMax = InMap.size() + InSetLocation.Y;
	int XMax = InMap[0].size() + InSetLocation.X;

	for (int y = 0; y < YMax; y++)
	{
		Temp.push_back(std::vector<Objects>());
		for (int x = 0; x < XMax; x++)
		{
			Temp[y].push_back(Objects::Empty);
		}
	}

	int YCount = Temp.size() - 1;
	int XCount = Temp[0].size() - 1;
	for (int y = InMap.size() - 1; y >= 0; y--)
	{
		for (int x = InMap[0].size() - 1; x >= 0; x--)
		{
			Temp[YCount][XCount] = InMap[y][x];
			XCount--;
		}
		XCount = Temp[0].size() - 1;
		YCount--;
	}
	InMap = Temp;

	return InMap;
}

bool MapGenerator::Direction4Object(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects CheckObject)
{
	int XMax = InMap1[0].size() > InMap2[0].size() ? InMap1[0].size() : InMap2[0].size();
	int YMax = InMap1.size() > InMap2.size() ? InMap1.size() : InMap2.size();
	for (int y = 0; y < YMax; y++)
	{
		for (int x = 0; x < XMax; x++)
		{
			if (InMap2[y][x] == CheckObject && InMap1[y][x] != CheckObject)//지금 체크할 오브젝트 구간에 왔다면
			{
				if (YMax > (y + 1) && InMap1[y + 1][x] == CheckObject)
				{
					return true;
				}
				if (0 <= (y - 1) && InMap1[y - 1][x] == CheckObject)
				{
					return true;
				}
				if (XMax > (x + 1) && InMap1[y][x + 1] == CheckObject)
				{
					return true;
				}
				if (0 <= (x - 1) && InMap1[y][x - 1] == CheckObject)
				{
					return true;
				}
			}
		}
	}
	return false;
}

