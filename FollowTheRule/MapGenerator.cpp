#include "MapGenerator.h"

MapGenerator::MapGenerator()
{
}

MapGenerator::MapGenerator(Vector InMapsMinSize, Vector InMapsMaxSize, int InTotalSmallMaps, int InSeed) 
	: MapsMinsize(InMapsMinSize), MapsMaxsize(InMapsMaxSize), TotalSmallMaps(InTotalSmallMaps), Seed(InSeed)
{

}

void MapGenerator::DebugMapViewer()
{
}

void MapGenerator::GeneratedMap()
{
	for (int i = 0; i < TotalSmallMaps; i++)
	{

	}
}

