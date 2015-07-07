#pragma once

#include <glrayfw/map/map.h>
#include "mapdata.h"

namespace mapgen
{



void Fill( Map& map );
Map RasterMapData( MapData& md );
//Map GenRooms( RNG& rng, mapgen::Config cfg );
void GenRooms( RNG& rng, mapgen::RoomGenConfig cfg, DynamicArray<Room>& list_rooms);
void RasterRooms( DynamicArray<Room>& rooms, Map& map, Map::BlockType block_type = Map::BLOCK_FREE );
void RasterPaths( DynamicArray<Room>& rooms, Map& map, Map::BlockType block_type = Map::BLOCK_FREE );
int sign( int x );
void HCorridor( Map& map, int x0, int x1, int y, Map::BlockType block_type = Map::BLOCK_FREE );
void VCorridor( Map& map, int y0, int y1, int x, Map::BlockType block_type = Map::BLOCK_FREE );
Map Flatten( Map map );
Map Decorate( Map map );
Map ConstructRoomMap( Map map, DynamicArray<Room>& rooms );
};
