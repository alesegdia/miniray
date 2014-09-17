
#pragma once

enum CollisionLayer
{
	BOUNDARY = 			0x0001,
	PLAYER_BULLET = 	0x0002,
	PLAYER = 			0x0004,
	ENEMY_BULLET =		0x0004,
	ENEMY =				0x0008,
	MAP =				0x0010
};
