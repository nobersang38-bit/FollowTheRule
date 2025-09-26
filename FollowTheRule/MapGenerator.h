#pragma once
#include <vector>
#include "Object.h"
#include "ObjectsEnumClass.h"
#include "Vector.h"

enum class MapFilterType
{
	BackDepth = 0
};

//이벤트 오브젝트와 플레이어를 제외한 맵을 생성하는 클래스
//생성되는 즉시 맵도 생성합니다
class MapGenerator : Object
{
public:
	void Update() override;
	void Start() override;

	const std::vector<std::vector<Objects>>& GetMap() const { return Map; }

	void DebugMapViewer();
	void DebugIslandViewr();
	void DebugSmallMapsViewer();

	MapGenerator();
	MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed);



private:
	//네모가 여러개 겹쳐있는듯한 표준 맵
	std::vector<std::vector<Objects>> GenerateMiddleMap();

	/// <summary>
	/// 두개의 맵을 합쳐주는 함수(합치는데 겹치지 않으면 Island변수에 추가 합니다)
	/// </summary>
	/// <param name="InMap1"></param>
	/// <param name="InMap2"></param>
	/// <param name="InMapFilterType">BackDepth는 선택한 오브젝트가 앞의 물체에 가리는 것 처럼 보이게 해줌</param>
	/// <param name="InFilterObject">적용되는 오브젝트</param>
	std::vector<std::vector<Objects>> MapDepthFilter(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject);

	//전체 맵안에 있는 작은 맵을 생성하는 함수
	std::vector<std::vector<Objects>> GenerateSmallMap(const Vector InGenerateStartLocation = Vector(0, 0));

	std::vector<std::vector<Objects>> MapLocationSet(std::vector<std::vector<Objects>>& InMap, const Vector InSetLocation);

	//InMap2 기준으로 체크
	bool IsAreaOvelap(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2);

	void InSideWallsRemover(std::vector<std::vector<Objects>>& InMap);
	void SoloWallsRemover(std::vector<std::vector<Objects>>& InMap);
	void AroundAllWallSpaceCheckEdit(std::vector<std::vector<Objects>>& InMap);

	//바깥쪽에 벽이 없다면 채워 넣는 함수
	void FillAroundWall(std::vector<std::vector<Objects>>& InMap);

	//제일 가까운 거리 알아서 연결해줍니다
	//만들지 못한다면 false를 반환합니다
	bool RoadGenerator(std::vector<std::vector<Objects>>& MainMap, const std::vector<std::vector<Objects>>& InMap, const std::vector<std::vector<Objects>>& InMap2);

	//서로 제일 가까운 곳에 좌표를 알려줍니다//만약 가로나 세로방향으로 못간다면 Vector::Min()을 반환합니다
	std::vector<Vector> IslandMinVector(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2);
	//void IslandRoadConnector(std::vector<std::vector<Objects>>& InMap, Vector InLocation = Vector::Zero());
	Vector IsArounObject(const std::vector<std::vector<Objects>>& InMap, Vector InFindLocation, Objects InFindObject);
	bool IsArounObject(const std::vector<std::vector<Objects>>& InMap, Vector InFindLocation, Vector InCheckDirection, Objects InFindObject);


	std::vector<std::vector<Objects>> Map;

	std::vector<std::vector<std::vector<Objects>>> SmallMapTemp;

	Vector SmallMapsMinsize = Vector(5, 5);
	Vector SmallMapsMaxsize = Vector(15, 15);
	Vector SmallMapsMinLocation = Vector(10, 10);
	Vector SmallMapsMaxLocation = Vector(80, 80);



	int TotalSmallMaps = 60;
	int Seed = 0;
	//필요한거
	//길 배열 (규칙에 그거 넣을겁니다 통로에 관련된거)
	//
};
