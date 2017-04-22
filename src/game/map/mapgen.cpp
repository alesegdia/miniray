
#include "mapgen.h"
#include <glrayfw/core/random.h>
#include "mapdata.h"
#include <glrayfw/core/matrix2d.h>



namespace mapgen
{


void Fill( Matrix2D& map, int block )
{
    for( int x = 0; x < map.Cols(); x++ )
    for( int y = 0; y < map.Rows(); y++ )
	{
		map.Set( x, y, block );
	}
}

// pasarle el mapdata.rooms
void GenRooms( RNG& rng, mapgen::RoomGenConfig cfg, DynamicArray<Room>& list_rooms)
{
	int w, h;
	w = cfg.map_width;
	h = cfg.map_height;
	Matrix2D map(w, h);
    Fill(map, 1);
	int room_halfw = cfg.room_max_width / 2;
	int room_halfh = cfg.room_max_height / 2;

	for( int i = 0; i < cfg.num_rooms; i++ )
	{
		int room_x = rng.uniform( room_halfw+3, w - room_halfw-3 );
		int room_y = rng.uniform( room_halfh+3, h - room_halfh-3 );
		int room_w = rng.uniform( cfg.room_min_width, cfg.room_max_width );
		int room_h = rng.uniform( cfg.room_min_height, cfg.room_max_height );
		Room r(room_x, room_y, room_w, room_h);
		bool valid_room = true;
		if( cfg.overlap_control )
		{
			for( int j = 0; j < ((int)list_rooms.Size()); j++ )
			{
				if( r.Intersects( list_rooms[j] ) )
				{
					valid_room = false;
					i--;
					break;
				}
			}
			// set valid_room to false if overlaps with any existing room in list_rooms
		}
		if( valid_room )
		{
			printf("ROOM %d\n", i);
			r.Debug();
			list_rooms.Add(r);
		}
	}
}

Matrix2D RasterMapData( MapData& md )
{
	Matrix2D map(md.config.map_width, md.config.map_height);
    Fill( map, 1 );
	RasterRooms( md.rooms, map );
	RasterPaths( md.rooms, map );
	return Decorate(Flatten(map));
}

Matrix2D RasterMapData2( MapData& md )
{
	Matrix2D map(md.config.map_width, md.config.map_height);
    Fill( map, 1 );
	RasterRooms( md.rooms, map );
	RasterPaths( md.rooms, map );
	return Decorate(Flatten(map));
}


/*
void GenRooms( RNG& rng, mapgen::RoomGenConfig cfg )
{
	DynamicArray<Room> d;
	GenRooms( rng, cfg, d );
}
*/

Matrix2D Flatten( Matrix2D map )
{
	Matrix2D newmap(map);
	int bounds[8][2] = {
		{  1,  0 },
		{  1,  1 },
		{  0,  1 },
		{ -1,  1 },
		{ -1,  0 },
		{ -1, -1 },
		{  0, -1 },
		{  1, -1 }
	};
    for( int x = 0; x < map.Cols(); x++ )
    for( int y = 0; y < map.Rows(); y++ )
	{
		int nb=0;
        for( int i = 0; i < 8; i++ ) nb += (map.getScroll(x + bounds[i][0], y + bounds[i][1]) == 0 ? 0 : 1);
        if( nb == 8 ) newmap.Set(x, y, 0);
	}
	return newmap;
}

Matrix2D Decorate( Matrix2D map )
{
	Matrix2D newmap(map);
	int bounds[4][2] = {
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
	};
    for( int x = 0; x < map.Cols(); x++ )
    for( int y = 0; y < map.Rows(); y++ )
	{
		int hnb=0,vnb=0;
		for( int i = 0; i < 2; i++ )
            hnb += (map.getScroll( x + bounds[i][0], y + bounds[i][1] ) == 0 ? 0 : 1);
		for( int i = 2; i < 4; i++ )
            vnb += (map.getScroll( x + bounds[i][0], y + bounds[i][1] ) == 0 ? 0 : 1);
        if( (hnb - vnb == 0 || hnb + vnb == 1 ) && map.Get( x, y ) != 0 ) newmap.Set(x, y, 2);
	}
	return newmap;

}

void RasterRooms( DynamicArray<Room>& rooms, Matrix2D& map, int block_type )
{
	for( int i = 0; i < ((int)rooms.Size()); i++ )
	{
		printf("NG\n");
		Room r = rooms[i];
		for( int x = r.x - r.w/2; x < r.x + r.w/2; x++ )
		for( int y = r.y - r.h/2; y < r.y + r.h/2; y++ )
		{
			map.Set( x, y, block_type );
		}
	}
}

void RasterPaths( DynamicArray<Room>& rooms, Matrix2D& map, int block_type )
{
	for( int i = 0; i < (int)rooms.Size()-1; i++ )
	{
		Room r0 = rooms[i];
		Room r1 = rooms[i+1];
		HCorridor( map, r0.x, r1.x, r0.y, block_type );
		VCorridor( map, r0.y, r1.y, r1.x, block_type );
	}
}

int sign( int x )
{
	return (x >= 0) ? 1 : -1;
}

void HCorridor( Matrix2D& map, int x0, int x1, int y, int block_type )
{
	int dx = x1 - x0;
	for( int x = x0; x != x1; x += sign(dx) )
	{
		map.Set(x, y, block_type);
	}
}

void VCorridor( Matrix2D& map, int y0, int y1, int x, int block_type )
{
	int dy = y1 - y0;
	for( int y = y0; y != y1; y += sign(dy) )
	{
		map.Set(x, y, block_type);
	}
}


Matrix2D ConstructRoomMap( Matrix2D map, DynamicArray<Room>& rooms )
{
	Matrix2D ret(map);
	mapgen::Fill( ret, 0 );
	for( int i = 0; i < (int)rooms.Size(); i++ )
	{
		for( int x = rooms[i].Left(); x < rooms[i].Right(); x++ )
		for( int y = rooms[i].Top(); y < rooms[i].Bot(); y++ )
		{
			ret.Set( x, y, i+1 );
		}
	}
	RasterPaths( rooms, ret, 9 );
	return ret;
}

Matrix2D ConstructDoors( Matrix2D map )
{
	Matrix2D ret(map);
	
	return map;
}

}
