
#pragma once

#include "../core/random.h"
#include "cml/cml.h"

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

	void Debug()
	{
		printf("tl: (%d,%d), br: (%d,%d)\n", Top(), Left(), Bot(), Right() );
	}

	cml::vector2i RandomPosition( RNG& rng, int reduce = 0 )
	{
		int l,r,t,b;
		l = Left() + reduce;
		r = Right() - reduce;
		t = Top() + reduce;
		b = Bot() - reduce;
		if( l < 0 ) l = 0;
		if( r < 0 ) r = 0;
		if( t < 0 ) t = 0;
		if( b < 0 ) b = 0;
		return cml::vector2i(
				rng.uniform( Left() + reduce, Right() - reduce ), rng.uniform( Top() + reduce, Bot() - reduce ) );
	}

	int Left() { return x-floor(w/2.f); }
	int Top() { return y-floor(h/2.f); }
	int Right() { return x + floor(w/2.f); }
	int Bot() { return y + floor(h/2.f); }

};

struct RoomGenConfig
{
	int map_width, map_height;
	int num_rooms, room_max_width, room_max_height, room_min_width, room_min_height;
	bool overlap_control;
	RoomGenConfig() :
		num_rooms(7),
		room_max_width (15),
		room_max_height(15),
		overlap_control(true),
		room_min_width(8),
		room_min_height(8),
		map_width(64),
		map_height(64)
	{}
};

struct RoomConnection
{
	// PATH: camino entre dos habitaciones
	// WARP: teletransporte entre dos habitaciones
	// HACK: camino a traves de hackear un ordenador
	enum Type {
		PATH, WARP, HACK
	} type;
	// connected rooms
	Map::BlockType ids[2];

	bool operator==( const RoomConnection& other )
	{
		return ids[0] == other.ids[0] && ids[1] == other.ids[1] && type == other.type;
	}
};

struct Path
{
	Map::BlockType ids[2];
};

struct Intersection
{
	// posición de la interseccion
	int x, y;
	// identificadores de los tipos de bloque que intersectan
	Map::BlockType ids[2];
	// conexión que provoca la intersección
	RoomConnection connection;
};

struct MapData
{
	RoomGenConfig config;
	DynamicArray<Room> rooms;
	DynamicArray<RoomConnection> connections;
	
};

};
