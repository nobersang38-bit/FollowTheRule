#include "MapGenerator.h"
#include "Tools.h"

using T = Tools;

void MapGenerator::Start()
{

}

void MapGenerator::Update()
{

}

MapGenerator::MapGenerator()
{
	Map = GenerateMiddleMap();
	//DebugMapViewer();
	//DebugSmallMapsViewer();
}

MapGenerator::MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed) 
	: SmallMapsMinsize(InMapsMinSize), SmallMapsMaxsize(InMapsMaxSize), TotalSmallMaps(InTotalSmallMaps), Seed(InSeed)
{
	Map = GenerateMiddleMap();
	//DebugMapViewer();
	//DebugSmallMapsViewer();
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

void MapGenerator::DebugSmallMapsViewer()
{
	printf("SmallMap ��ΰ� : [%d]\n", static_cast<int>(SmallMapTemp.size()));
	for (int i = 0; i < SmallMapTemp.size(); i++)
	{
		printf("______________________________________________\n");
		for (int y = 0; y < SmallMapTemp[i].size(); y++)
		{
			for (int x = 0; x < SmallMapTemp[i][y].size(); x++)
			{
				switch (SmallMapTemp[i][y][x])
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
}

std::vector<std::vector<Objects>> MapGenerator::GenerateMiddleMap()
{
	std::vector<std::vector<Objects>> Temp;
	Temp.push_back(std::vector<Objects>());
	Temp[0].push_back(Objects::Empty);
	//Map[0].push_back(Objects::)
	for (int i = 0; i < TotalSmallMaps; i++)
	{
		Temp = MapDepthFilter(Temp, GenerateSmallMap(Vector(T::RandomRange(SmallMapsMinLocation.X, SmallMapsMaxLocation.X), T::RandomRange(SmallMapsMinLocation.Y, SmallMapsMaxLocation.Y))), Objects::Empty);
		InSideWallsRemover(Temp);
		SoloWallsRemover(Temp);
		FillAroundWall(Temp);
		AroundAllWallSpaceCheckEdit(Temp);
	}
	return Temp;
}

std::vector<std::vector<Objects>> MapGenerator::MapDepthFilter(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject)
{

	std::vector<std::vector<Objects>> TempMap;
	int XMax = InMap1[0].size() > InMap2[0].size() ? InMap1[0].size() : InMap2[0].size();
	int YMax = InMap1.size() > InMap2.size() ? InMap1.size() : InMap2.size();
	SmallMapTemp.push_back(std::vector<std::vector<Objects>>(InMap2));//���ϳ� �߰�

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
	if (!IsAreaOvelap(InMap1, InMap2))//�浹���ϸ� ���� ������ �մϴ�
	{
		//printf("�浹 ���մϴ�!! \n\n");

		if (!RoadGenerator(TempMap, InMap1, InMap2))//�̺κ� false ��ȯ�ϸ� InMap2 �߰��ϸ� �ȵ˴ϴ�
		{
			return TempMap;
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
	Vector MapSize = Vector(T::RandomRange(SmallMapsMinsize.X, SmallMapsMaxsize.X), T::RandomRange(SmallMapsMinsize.Y, SmallMapsMaxsize.Y));

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

bool MapGenerator::IsAreaOvelap(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2)
{
	int XMax = InMap1[0].size() < InMap2[0].size() ? InMap1[0].size() : InMap2[0].size();
	int YMax = InMap1.size() < InMap2.size() ? InMap1.size() : InMap2.size();

	for (int y = 0; y < YMax; y++)
	{
		for (int x = 0; x < XMax; x++)
		{
			if (InMap1[y][x] != Objects::Empty && InMap2[y][x] != Objects::Empty)//�̰� ���� �ε������� �Ѵ� ���� ��ġ�� ������� �����ϱ�
			{
				return true;
			}
		}
	}
	return false;
	//for (int y = 0; y < YMax; y++)
	//{
	//	for (int x = 0; x < XMax; x++)
	//	{
	//		if (InMap2[y][x] == CheckObject)//���� üũ�� ������Ʈ ������ �Դٸ�
	//		{
	//			if (YMax > (y + 1) && InMap1[y + 1][x] == CheckObject)
	//			{
	//				return true;
	//			}
	//			if (0 <= (y - 1) && InMap1[y - 1][x] == CheckObject)
	//			{
	//				return true;
	//			}
	//			if (XMax > (x + 1) && InMap1[y][x + 1] == CheckObject)
	//			{
	//				return true;
	//			}
	//			if (0 <= (x - 1) && InMap1[y][x - 1] == CheckObject)
	//			{
	//				return true;
	//			}
	//		}
	//	}
	//}
	//return false;
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

void MapGenerator::AroundAllWallSpaceCheckEdit(std::vector<std::vector<Objects>>& InMap)
{
	for (int y = 0; y < InMap.size(); y++)
	{
		for (int x = 0; x < InMap[0].size(); x++)
		{
			if (InMap[y][x] == Objects::Space)
			{
				if (
					IsArounObject(InMap, Vector(x, y), Vector::Up(), Objects::Wall) &&
					IsArounObject(InMap, Vector(x, y), Vector::Down(), Objects::Wall)&&
					IsArounObject(InMap, Vector(x, y), Vector::Left(), Objects::Wall)&&
					IsArounObject(InMap, Vector(x, y), Vector::Right(), Objects::Wall)
					)
				{
					InMap[y + 1][x] = Objects::Space;
					InMap[y - 1][x] = Objects::Space;
					InMap[y][x + 1] = Objects::Space;
					InMap[y][x - 1] = Objects::Space;

					if (InMap[y + 1][x + 1] == Objects::Empty)
					{
						InMap[y + 1][x + 1] = Objects::Wall;
						InMap[y - 1][x - 1] = Objects::Wall;
					}
					else if (InMap[y + 1][x - 1] == Objects::Empty)
					{
						InMap[y + 1][x - 1] = Objects::Wall;
						InMap[y - 1][x + 1] = Objects::Wall;
					}
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
		}
	}
}

bool MapGenerator::RoadGenerator(std::vector<std::vector<Objects>>& MainMap, const std::vector<std::vector<Objects>>& InMap,const std::vector<std::vector<Objects>>& InMap2)
{
	std::vector<Vector> MinDisLocation = IslandMinVector(InMap, InMap2);
	if (MinDisLocation[0] == Vector::Min() && MinDisLocation[1] == Vector::Min())
	{
		//printf("�� ������ϴ�");
		return false;
	}
	//printf("�ִ� ��ο� �ִ� �� ��ġ [%d, %d] [%d, %d]", MinDisLocation[0].X, MinDisLocation[0].Y, MinDisLocation[1].X, MinDisLocation[1].Y);

	if (MinDisLocation[0].X == MinDisLocation[1].X)//�̰� ���η� ���� �ǰ���
	{
		int YMax = 0;
		int YMin = 0;
		if (MinDisLocation[0].Y > MinDisLocation[1].Y)
		{
			YMax = MinDisLocation[0].Y;
			YMin = MinDisLocation[1].Y;
		}
		else
		{
			YMax = MinDisLocation[1].Y;
			YMin = MinDisLocation[0].Y;
		}

		for (int y = YMin; y <= YMax; y++)//�� �����
		{
			MainMap[y][MinDisLocation[0].X] = Objects::Space;

			if(MinDisLocation[0].X + 1 < MainMap[0].size())
			MainMap[y][MinDisLocation[0].X + 1] = Objects::Wall;

			if(MinDisLocation[0].X - 1 >= 0)
			MainMap[y][MinDisLocation[0].X - 1] = Objects::Wall;
		}
	}
	else if (MinDisLocation[0].Y == MinDisLocation[1].Y)//�̰� ���η� ���� �ǰ���
	{
		int XMax = 0;
		int XMin = 0;
		if (MinDisLocation[0].X > MinDisLocation[1].X)
		{
			XMax = MinDisLocation[0].X;
			XMin = MinDisLocation[1].X;
		}
		else
		{
			XMax = MinDisLocation[1].X;
			XMin = MinDisLocation[0].X;
		}

		for (int x = XMin; x <= XMax; x++)//�� �����
		{
			MainMap[MinDisLocation[0].Y][x] = Objects::Space;

			if (MinDisLocation[0].Y + 1 < MainMap.size())
				MainMap[MinDisLocation[0].Y + 1][x] = Objects::Wall;

			if (MinDisLocation[0].Y - 1 >= 0)
				MainMap[MinDisLocation[0].Y - 1][x] = Objects::Wall;
		}
	}

	return true;
}

std::vector<Vector> MapGenerator::IslandMinVector(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2)
{
	int MinDistance = INT_MAX;
	std::vector<Vector> Temp;
	Temp.push_back(Vector::Zero());
	Temp.push_back(Vector::Zero());
	for (int y = 0; y < InMap1.size(); y++)
	{
		for (int x = 0; x < InMap1[0].size(); x++)
		{
			if (InMap1[y][x] == Objects::Wall)
			{
				for (int i = 0; i < InMap2.size(); i++)
				{
					for (int j = 0; j < InMap2[0].size(); j++)
					{
						if (InMap2[i][j] == Objects::Wall &&
							(Vector(x, y) - Vector(j, i)).Magnitude() < MinDistance
							)
						{
							if (y == i || x == j)//���� �����̳� ���� �������� �� �� �ִٸ�
							{
								MinDistance = (Vector(x, y) - Vector(j, i)).Magnitude();
								Temp[0] = Vector(x, y);
								Temp[1] = Vector(j, i);
							}
							else
							{
								Temp[0] = Vector::Min();
								Temp[1] = Vector::Min();
							}
						}
					}
				}
			}
		}
	}
	return Temp;
}


//void MapGenerator::IslandRoadConnector(std::vector<std::vector<Objects>>& InMap, Vector InLocation)//���� ã���� �ϴ� ������ ���Ƽ� �� ���θ� �� �� �� �ִ��� Ȯ�� �սô�/�̰� �����ϸ� �� ���鶧 ����ؼ� �սô�
//{
//	std::vector<std::vector<Objects>> Temp = std::vector<std::vector<Objects>>(InMap);
//
//	if (Temp.size() <= InLocation.Y || 0 > InLocation.Y ||
//		Temp[0].size() <= InLocation.X || 0 > InLocation.X
//		)
//	{
//		printf("�׽�Ʈ!!!   ");
//		return;
//	}
//	if (Temp[InLocation.Y][InLocation.X] == Objects::Space)
//	{
//		printf("%d  %d", (InLocation + Vector::Up()).Y, (InLocation + Vector::Up()).X);
//		IslandRoadConnector(Temp, InLocation + Vector::Up());
//		IslandRoadConnector(Temp, InLocation + Vector::Down());
//		IslandRoadConnector(Temp, InLocation + Vector::Left());
//		IslandRoadConnector(Temp, InLocation + Vector::Right());
//	}
//	if (Temp[InLocation.Y][InLocation.X] == Objects::Wall)
//	{
//		printf("�׽�Ʈ");
//		return;
//	}
//}

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

bool MapGenerator::IsArounObject(const std::vector<std::vector<Objects>>& InMap, Vector InFindLocation, Vector InCheckDirection, Objects InFindObject)
{
	int YMax = InMap.size();
	int XMax = InMap[0].size();
	if (
		YMax <= InFindLocation.Y || 0 > InFindLocation.Y ||
		XMax <= InFindLocation.X || 0 > InFindLocation.X
		)
	{
		return false;
	}

	if (YMax > (InFindLocation.Y + 1) && InCheckDirection == Vector::Up() && InMap[InFindLocation.Y + 1][InFindLocation.X] == InFindObject)
	{
		return true;
	}
	if (0 <= (InFindLocation.Y - 1) && InCheckDirection == Vector::Down() && InMap[InFindLocation.Y - 1][InFindLocation.X] == InFindObject)
	{
		return true;
	}
	if (0 <= (InFindLocation.X - 1) && InCheckDirection == Vector::Left() && InMap[InFindLocation.Y][InFindLocation.X - 1] == InFindObject)
	{
		return true;
	}
	if (XMax > (InFindLocation.X + 1) && InCheckDirection == Vector::Right() && InMap[InFindLocation.Y][InFindLocation.X + 1] == InFindObject)
	{
		return true;
	}

	return false();
}


