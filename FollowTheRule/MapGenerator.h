#pragma once
#include <vector>
#include "ObjectsEnumClass.h"
#include "Vector.h"

enum class MapFilterType
{
	BackDepth = 0
};

//이벤트 오브젝트와 플레이어를 제외한 맵을 생성하는 클래스
//생성되는 즉시 맵도 생성합니다
class MapGenerator
{
public:
	MapGenerator();
	MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed);

	void DebugMapViewer();
private:
public:
	//네모가 여러개 겹쳐있는듯한 표준 맵
	std::vector<std::vector<Objects>> GenerateMiddleMap();

	/// <summary>
	/// 두개의 맵을 합쳐주는 함수
	/// </summary>
	/// <param name="InMap1"></param>
	/// <param name="InMap2"></param>
	/// <param name="InMapFilterType">BackDepth는 선택한 오브젝트가 앞의 물체에 가리는 것 처럼 보이게 해줌</param>
	/// <param name="InFilterObject">적용되는 오브젝트</param>
	std::vector<std::vector<Objects>> MapDepthFilter(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject);

	//전체 맵안에 있는 작은 맵을 생성하는 함수
	std::vector<std::vector<Objects>> GenerateSmallMap(const Vector InGenerateStartLocation = Vector(0, 0));

	std::vector<std::vector<Objects>> MapLocationSet(std::vector<std::vector<Objects>>& InMap, const Vector InSetLocation);

	bool Direction4Object(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects CheckObject);

	std::vector<std::vector<Objects>> Map;

	Vector SmallMapsMinsize = Vector(10, 10);
	Vector SmallMapsMaxsize = Vector(25, 25);
	Vector SmallMapsMinLocation = Vector(10, 10);
	Vector SmallMapsMaxLocation = Vector(50, 50);

	int TotalSmallMaps = 10;
	int Seed = 0;

	//이거는 아직 넣지 맙시다 사각형 완성되고 ㄱ
	float Noise = 0.0f;
};
