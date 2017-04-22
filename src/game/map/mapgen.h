#pragma once

#include <glrayfw/core/matrix2d.h>
#include <glrayfw/core/dynamicarray.h>
#include "mapdata.h"

namespace mapgen
{



void Fill( Matrix2D& map );
Matrix2D RasterMapData( MapData& md );
//Map GenRooms( RNG& rng, mapgen::Config cfg );
void GenRooms( RNG& rng, mapgen::RoomGenConfig cfg, DynamicArray<Room>& list_rooms);
void RasterRooms( DynamicArray<Room>& rooms, Matrix2D& map, int block_type = 0 );
void RasterPaths( DynamicArray<Room>& rooms, Matrix2D& map, int block_type = 0 );
int sign( int x );
void HCorridor( Matrix2D& map, int x0, int x1, int y, int block_type = 0 );
void VCorridor( Matrix2D& map, int y0, int y1, int x, int block_type = 0 );
Matrix2D Flatten( Matrix2D map );
Matrix2D Decorate( Matrix2D map );
Matrix2D ConstructRoomMap( Matrix2D map, DynamicArray<Room>& rooms );

};
