#include "Enemy.h"
#include "ObjectsEnumClass.h"
#include "Tools.h"

using T = Tools;

Enemy::Enemy(const std::vector<std::vector<int64_t>>* InMap, Vector* InPlayerPosition, Vector InLocation)
{
	Map = InMap;
	PlayerPosition = InPlayerPosition;
	Position = InLocation;
}

void Enemy::Start()
{
}

void Enemy::Update()
{
	if (TempTime > 0.6f)
	{
		TempTime = 0.0f;
		int YMax = T::Clamp(Position.Y + DetectDistance, 0, Map->size() - 1);
		int YMin = T::Clamp(Position.Y - DetectDistance, 0, Map->size() - 1);
		int XMax = T::Clamp(Position.X + DetectDistance, 0, Map->size() - 1);
		int XMin = T::Clamp(Position.X - DetectDistance, 0, Map->size() - 1);

		RevertPosition = Position;

		if ((*PlayerPosition - Position).Magnitude() < DetectDistance)
		{
			Vector Direction = *PlayerPosition - Position;

			if (Direction.X > 0)//오른쪽에 있다면
			{
				Position += Vector::Right();
			}
			else if (Direction.X < 0)//왼쪽에 있다면
			{
				Position += Vector::Left();
			}
			if (Direction.Y > 0)//위쪽에 있다면
			{
				Position += Vector::Up();
			}
			else if (Direction.Y < 0)//아래쪽에 있다면
			{
				Position += Vector::Down();
			}
		}
		//for (int y = YMin; y < YMax; y++)
		//{
		//	for (int x = XMin; x < XMax; x++)
		//	{
		//		if ((*Map)[y][x] & static_cast<int8_t>(Objects::Player))
		//		{
		//			Vector Direction = Vector(x, y) - Position;

		//			if (Direction.X > 0)//오른쪽에 있다면
		//			{
		//				Position += Vector::Right();
		//			}
		//			else if (Direction.X < 0)//왼쪽에 있다면
		//			{
		//				Position += Vector::Left();
		//			}
		//			if (Direction.Y > 0)//위쪽에 있다면
		//			{
		//				Position += Vector::Up();
		//			}
		//			else if (Direction.Y < 0)//아래쪽에 있다면
		//			{
		//				Position += Vector::Down();
		//			}
		//		}
		//	}
		//}
	}
	TempTime += T::DeletaTime();
}
