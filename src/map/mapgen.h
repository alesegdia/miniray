#pragma once

#include "map.h"

namespace mapgen
{

struct Room
{
	int x, y, w, h;
	Room( int x, int y, int w, int h ) { this->x = x; this->y = y; this->w = w; this->h = h; }
	bool Intersects( Room& other )
	{
		int t0, t1, b0, b1, l0, l1, r0, r1;
		t0 = y - h/2; t1 = other.y - other.h/2;
		b0 = y + h/2; b1 = other.y + other.h/2;
		l0 = x - w/2; l1 = other.x - other.w/2;
		r0 = x + w/2; r1 = other.x + other.w/2;
		return !(l1 > r0 || r1 < l0 || t1 > b0 || b1 < t0);
	}
};

struct Config
{
	int map_width, map_height;
	int num_rooms, room_max_width, room_max_height, room_min_width, room_min_height;
	bool overlap_control;
	Config() :
		num_rooms(10),
		room_max_width (10),
		room_max_height(10),
		overlap_control(true),
		room_min_width(4),
		room_min_height(4),
		map_width(64),
		map_height(36)
	{}
};

void Fill( Map& map );
Map Generar( mapgen::Config cfg );
void RasterRooms( DynamicArray<Room>& rooms, Map& map );
void RasterPaths( DynamicArray<Room>& rooms, Map& map );
int sign( int x );
void HCorridor( Map& map, int x0, int x1, int y );
void VCorridor( Map& map, int y0, int y1, int x );
Map Flatten( Map map );
Map Decorate( Map map );

};
