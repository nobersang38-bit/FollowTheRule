#pragma once
#include <vector>
#include "Object.h"
#include "ObjectsEnumClass.h"
#include "Vector.h"

enum class MapFilterType
{
	BackDepth = 0
};

//�̺�Ʈ ������Ʈ�� �÷��̾ ������ ���� �����ϴ� Ŭ����
//�����Ǵ� ��� �ʵ� �����մϴ�
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
	//�׸� ������ �����ִµ��� ǥ�� ��
	std::vector<std::vector<Objects>> GenerateMiddleMap();

	/// <summary>
	/// �ΰ��� ���� �����ִ� �Լ�(��ġ�µ� ��ġ�� ������ Island������ �߰� �մϴ�)
	/// </summary>
	/// <param name="InMap1"></param>
	/// <param name="InMap2"></param>
	/// <param name="InMapFilterType">BackDepth�� ������ ������Ʈ�� ���� ��ü�� ������ �� ó�� ���̰� ����</param>
	/// <param name="InFilterObject">����Ǵ� ������Ʈ</param>
	std::vector<std::vector<Objects>> MapDepthFilter(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2, Objects InFilterObject);

	//��ü �ʾȿ� �ִ� ���� ���� �����ϴ� �Լ�
	std::vector<std::vector<Objects>> GenerateSmallMap(const Vector InGenerateStartLocation = Vector(0, 0));

	std::vector<std::vector<Objects>> MapLocationSet(std::vector<std::vector<Objects>>& InMap, const Vector InSetLocation);

	//InMap2 �������� üũ
	bool IsAreaOvelap(const std::vector<std::vector<Objects>>& InMap1, const std::vector<std::vector<Objects>>& InMap2);

	void InSideWallsRemover(std::vector<std::vector<Objects>>& InMap);
	void SoloWallsRemover(std::vector<std::vector<Objects>>& InMap);
	void AroundAllWallSpaceCheckEdit(std::vector<std::vector<Objects>>& InMap);

	//�ٱ��ʿ� ���� ���ٸ� ä�� �ִ� �Լ�
	void FillAroundWall(std::vector<std::vector<Objects>>& InMap);

	//���� ����� �Ÿ� �˾Ƽ� �������ݴϴ�
	//������ ���Ѵٸ� false�� ��ȯ�մϴ�
	bool RoadGenerator(std::vector<std::vector<Objects>>& MainMap, const std::vector<std::vector<Objects>>& InMap, const std::vector<std::vector<Objects>>& InMap2);

	//���� ���� ����� ���� ��ǥ�� �˷��ݴϴ�//���� ���γ� ���ι������� �����ٸ� Vector::Min()�� ��ȯ�մϴ�
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
	//�ʿ��Ѱ�
	//�� �迭 (��Ģ�� �װ� �����̴ϴ� ��ο� ���õȰ�)
	//
};
