
#include "mapgen.h"
#include "../core/random.h"



namespace mapgen
{

RNG rng;

void Fill( Map& map, Map::BlockType block )
{
	for( int x = 0; x < map.Width(); x++ )
	for( int y = 0; y < map.Height(); y++ )
	{
		map.Set( x, y, block );
	}
}

Map Generar(  mapgen::Config cfg )
{
	int w, h;
	w = cfg.map_width;
	h = cfg.map_height;
	Map map(w, h);
	Fill(map, Map::BLOCK_SOLID);
	DynamicArray<Room> list_rooms;
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
			for( int j = 0; j < list_rooms.Size(); j++ )
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
		if( valid_room ) list_rooms.Add(r);
	}

	RasterRooms( list_rooms, map );
	RasterPaths( list_rooms, map );
	return Decorate(Flatten(map));

}

Map Flatten( Map map )
{
	Map newmap(map);
	int bounds[8][2] = {
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ -1, 1 },
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1 }
	};
	for( int x = 1; x < map.Width(); x++ )
	for( int y = 1; y < map.Height(); y++ )
	{
		int nb=0;
		for( int i = 0; i < 8; i++ ) nb += (map.Getint((x+bounds[i][0]) % map.Width(), (y+bounds[i][1]) % map.Height()) == Map::BLOCK_FREE ? 0 : 1);
		if( nb == 8 ) newmap.Set(x, y, Map::BLOCK_FREE);
	}
	return newmap;
}

Map Decorate( Map map )
{
	Map newmap(map);
	int bounds[4][2] = {
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
	};
	for( int x = 0; x < map.Width(); x++ )
	for( int y = 0; y < map.Height(); y++ )
	{
		int hnb=0,vnb=0;
		for( int i = 0; i < 2; i++ )
			hnb += (map.Getint((x+bounds[i][0]) % map.Width(), (y+bounds[i][1]) % map.Height()) == Map::BLOCK_FREE ? 0 : 1);
		for( int i = 2; i < 4; i++ )
			vnb += (map.Getint((x+bounds[i][0]) % map.Width(), (y+bounds[i][1]) % map.Height()) == Map::BLOCK_FREE ? 0 : 1);
		if( (hnb - vnb == 0 || hnb + vnb == 1 ) && map.Getint( x, y ) != Map::BLOCK_FREE ) newmap.Set(x, y, 2);
	}
	return newmap;

}

void RasterRooms( DynamicArray<Room>& rooms, Map& map )
{
	for( int i = 0; i < rooms.Size(); i++ )
	{
		Room r = rooms[i];
		for( int x = r.x - r.w/2; x < r.x + r.w/2; x++ )
		for( int y = r.y - r.h/2; y < r.y + r.h/2; y++ )
		{
			map.Set( x, y, Map::BLOCK_FREE );
		}
	}
}

void RasterPaths( DynamicArray<Room>& rooms, Map& map )
{
	for( int i = 0; i < rooms.Size()-1; i++ )
	{
		Room r0 = rooms[i];
		Room r1 = rooms[i+1];
		HCorridor( map, r0.x, r1.x, r0.y );
		VCorridor( map, r0.y, r1.y, r1.x );
	}
}

int sign( int x )
{
	return (x >= 0) ? 1 : -1;
}

void HCorridor( Map& map, int x0, int x1, int y )
{
	int dx = x1 - x0;
	for( int x = x0; x != x1; x += sign(dx) )
	{
		map.Set(x, y, Map::BLOCK_FREE);
	}
}

void VCorridor( Map& map, int y0, int y1, int x )
{
	int dy = y1 - y0;
	for( int y = y0; y != y1; y += sign(dy) )
	{
		map.Set(x, y, Map::BLOCK_FREE);
	}
}

}
