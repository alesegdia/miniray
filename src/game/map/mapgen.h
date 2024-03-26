#pragma once

#include <glrayfw/core/matrix2d.h>
#include <glrayfw/core/dynamicarray.h>
#include "mapdata.h"

namespace mapgen
{



void Fill( Matrix2D& map );
Matrix2D RasterMapData( const MapData& md );
//Map GenRooms( RNG& rng, mapgen::Config cfg );
MapData GenRooms( RNG& rng, mapgen::RoomGenConfig cfg);
void RasterRooms( const DynamicArray<Room>& rooms, Matrix2D& map, int block_type = 0 );
void RasterPaths( const DynamicArray<Room>& rooms, Matrix2D& map, int block_type = 0 );
int sign( int x );
void HCorridor(Matrix2D& map, int x0, int x1, int y, int block_type = 0);
void VCorridor(Matrix2D& map, int y0, int y1, int x, int block_type = 0);
void CanHCorridor( const mapgen::MapData& md, int x0, int x1, int y );
void CanVCorridor( const mapgen::MapData& md, int y0, int y1, int x );
Matrix2D Flatten( Matrix2D map );
Matrix2D Decorate( Matrix2D map );
Matrix2D ConstructRoomMap( Matrix2D map, DynamicArray<Room>& rooms );

};
