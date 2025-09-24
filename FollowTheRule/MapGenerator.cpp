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

void MapGenerator::DebugIslandViewr()
{
}

std::vector<std::vector<Objects>> MapGenerator::GenerateMiddleMap()
{
	std::vector<std::vector<Objects>> Temp;
	Temp.push_back(std::vector<Objects>());
	Temp[0].push_back(Objects::Empty);
	//Map[0].push_back(Objects::)
	for (int i = 0; i < TotalSmallMaps; i++)
	{
		Temp = MapDepthFilter(Temp, GenerateSmallMap(Vector(RandomRange(SmallMapsMinLocation.X, SmallMapsMaxLocation.X), RandomRange(SmallMapsMinLocation.Y, SmallMapsMaxLocation.Y))), Objects::Empty);
		InSideWallsRemover(Temp);
		SoloWallsRemover(Temp);
		FillAroundWall(Temp);
		IslandRoadConnector(Temp);
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

	//�ʻ���� �������� ���մϴ�
	Vector MapSize = Vector(RandomRange(SmallMapsMinsize.X, SmallMapsMaxsize.X), RandomRange(SmallMapsMinsize.Y, SmallMapsMaxsize.Y));

	//�ʻ��� ��ġ �����?
	for (int y = 0; y < InGenerateStartLocation.Y + MapSize.Y; y++)
	{
		Map.push_back(std::vector<Objects>());
		for (int x = 0; x < InGenerateStartLocation.X + MapSize.X; x++)
		{
			Map[y].push_back(Objects::Empty);
		}
	}

	//������ �迭 �����ϴ� ����
	int YMin = InGenerateStartLocation.Y;
	int YMax = InGenerateStartLocation.Y + MapSize.Y;

	int XMin = InGenerateStartLocation.X;
	int XMax = InGenerateStartLocation.X + MapSize.X;

	for (int y = YMin; y < YMax; y++)
	{
		for (int x = XMin; x < XMax; x++)
		{
			if	(	
					( y == YMin || y == (YMax - 1) ) ||	//Y��ǥ�� ó���̰ų� ���κ��̶��
					( x == XMin || x == (XMax - 1) )		//X��ǥ�� ó���̰ų� ���κ��̶��
				)
			{
				Map[y][x] = Objects::Wall;
			}
			else //������ �� �ִ� ����� �����
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
	int XMax = InMap1[0].size() < InMap2[0].size() ? InMap1[0].size() : InMap2[0].size();
	int YMax = InMap1.size() < InMap2.size() ? InMap1.size() : InMap2.size();

	for (int y = 0; y < YMax; y++)
	{
		for (int x = 0; x < XMax; x++)
		{
			if (InMap2[y][x] == CheckObject)//���� üũ�� ������Ʈ ������ �Դٸ�
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

void MapGenerator::InSideWallsRemover(std::vector<std::vector<Objects>>& InMap)
{
	for (int y = 0; y < InMap.size(); y++)
	{
		for (int x = 0; x < InMap[0].size(); x++)
		{
			if (InMap[y][x] == Objects::Wall)
			{
				int YUp = y + 1;
				int YDown = y - 1;
				int XLeft = x - 1;
				int XRight = x + 1;

				if (
					(InMap.size() <= YUp || InMap[YUp][x] == Objects::Empty) ||
					(0 > YDown || InMap[YDown][x] == Objects::Empty) ||
					(0 > XLeft || InMap[y][XLeft] == Objects::Empty) ||
					(InMap[0].size() <= XRight || InMap[y][XRight] == Objects::Empty)
					) continue;

				int XCount = 0;
				int YCount = 0;
				if (InMap.size() > YUp && InMap[YUp][x] == Objects::Wall)//�̰� ���������� �����ؾ��մϴ�
				{
					XCount = x;
					while (XCount < InMap[0].size() && InMap[YUp][XCount] == Objects::Wall)
					{
						InMap[y][XCount] = Objects::Space;
						XCount++;
					}
				}
				if (0 <= YDown && InMap[YDown][x] == Objects::Wall)//�̰� ���������� �����ؾ��մϴ�
				{
					XCount = x;
					while (XCount < InMap[0].size() && InMap[YDown][XCount] == Objects::Wall)
					{
						InMap[y][XCount] = Objects::Space;
						XCount++;
					}
				}

				if (0 <= XLeft && InMap[y][XLeft] == Objects::Wall)//�̰� �Ʒ������� �����ؾ��մϴ�
				{
					YCount = y;
					while (0 <= YCount && InMap[YCount][XLeft] == Objects::Wall)
					{
						InMap[YCount][x] = Objects::Space;
						YCount--;
					}
				}
				if (InMap[0].size() > XRight && InMap[y][XRight] == Objects::Wall)//�̰� �Ʒ������� �����ؾ��մϴ�
				{
					YCount = y;
					while (0 <= YCount && InMap[YCount][XRight] == Objects::Wall)
					{
						InMap[YCount][x] = Objects::Space;
						YCount--;
					}
				}
			}
		}
	}
}

void MapGenerator::SoloWallsRemover(std::vector<std::vector<Objects>>& InMap)
{
	for (int y = 0; y < InMap.size(); y++)
	{
		for (int x = 0; x < InMap[0].size(); x++)
		{
			if (InMap[y][x] == Objects::Wall)
			{
				Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Wall);
				if (WallDirection == Vector::Zero())
				{
					InMap[y][x] = Objects::Space;
				}
			}
		}
	}
}

void MapGenerator::FillAroundWall(std::vector<std::vector<Objects>>& InMap)
{
	for (int y = 0; y < InMap.size(); y++)
	{
		for (int x = 0; x < InMap[0].size(); x++)
		{
			if (InMap[y][x] == Objects::Space)
			{
				Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Empty);
				if (WallDirection != Vector::Zero() || x == (InMap[0].size()-1))
				{
					InMap[y][x] = Objects::Wall;
					continue;
				}
			}

			//if (InMap[y][x] == Objects::Wall)//�ε����� ���� ������ �� �κ��� �����̽� ���κ��� Empty���� �Ѵ�
			//{
			//	int YUp = y + 1;
			//	int YDown = y - 1;
			//	int XLeft = x - 1;
			//	int XRight = x + 1;
			//	if (YUp < InMap.size() && InMap[YUp][x] == Objects::Space)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Empty);
			//		if (WallDirection == Vector::Right() || WallDirection == Vector::Left())
			//		{
			//			InMap[YUp][x] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (YDown >= 0 && InMap[YDown][x] == Objects::Space)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Empty);
			//		if (WallDirection == Vector::Right() || WallDirection == Vector::Left())
			//		{
			//			InMap[YDown][x] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (XLeft >= 0 && InMap[y][XLeft] == Objects::Space)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Empty);
			//		if (WallDirection == Vector::Up() || WallDirection == Vector::Down())
			//		{
			//			InMap[y][XLeft] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (XRight < InMap[0].size() && InMap[y][XRight] == Objects::Space)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Empty);
			//		if (WallDirection == Vector::Up() || WallDirection == Vector::Down())
			//		{
			//			InMap[y][XRight] = Objects::Wall;
			//			continue;
			//		}
			//	}

			//	//�̰� ���� �ű�� �� �ű�������
			//	if (YUp < InMap.size() && InMap[YUp][x] == Objects::Empty)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Space);
			//		if (WallDirection == Vector::Right() || WallDirection == Vector::Left())
			//		{
			//			InMap[YUp][x] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (YDown >= 0 && InMap[YDown][x] == Objects::Empty)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Space);
			//		if (WallDirection == Vector::Right() || WallDirection == Vector::Left())
			//		{
			//			InMap[YDown][x] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (XLeft >= 0 && InMap[y][XLeft] == Objects::Empty)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Space);
			//		if (WallDirection == Vector::Up() || WallDirection == Vector::Down())
			//		{
			//			InMap[y][XLeft] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//	else if (XRight < InMap[0].size() && InMap[y][XRight] == Objects::Empty)
			//	{
			//		Vector WallDirection = IsArounObject(InMap, Vector(x, y), Objects::Space);
			//		if (WallDirection == Vector::Up() || WallDirection == Vector::Down())
			//		{
			//			InMap[y][XRight] = Objects::Wall;
			//			continue;
			//		}
			//	}
			//}
		}
	}
}


void MapGenerator::IslandRoadConnector(std::vector<std::vector<Objects>>& InMap)//���� ã���� �ϴ� ������ ���Ƽ� �� ���θ� �� �� �� �ִ��� Ȯ�� �սô�
{
	std::vector<std::vector<Objects>> Temp = std::vector<std::vector<Objects>>(InMap);

}

Vector MapGenerator::IsArounObject(const std::vector<std::vector<Objects>>& InMap, Vector InFindLocation, Objects InFindObject)
{
	int YMax = InMap.size();
	int XMax = InMap[0].size();
	if (
			YMax <= InFindLocation.Y || 0 > InFindLocation.Y ||
			XMax <= InFindLocation.X || 0 > InFindLocation.X
		)
	{
		return Vector::Zero();
	}

	if (YMax > (InFindLocation.Y + 1) && InMap[InFindLocation.Y + 1][InFindLocation.X] == InFindObject)
	{
		return Vector::Up();
	}
	if (0 <= (InFindLocation.Y - 1) && InMap[InFindLocation.Y - 1][InFindLocation.X] == InFindObject)
	{
		return Vector::Down();
	}
	if (0 <= (InFindLocation.X - 1) && InMap[InFindLocation.Y][InFindLocation.X - 1] == InFindObject)
	{
		return Vector::Left();
	}
	if (XMax > (InFindLocation.X + 1) && InMap[InFindLocation.Y][InFindLocation.X + 1] == InFindObject)
	{
		return Vector::Right();
	}

	return Vector::Zero();
}
