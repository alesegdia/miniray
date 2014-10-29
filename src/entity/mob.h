
#pragma once

#include "actor.h"
#include "../constants.h"

class Mob : public Actor
{

public:

	// mas alto, mas pro
	int handicap;

	bool player_visible;
	float player_distance;
	float angle_to_player;

	struct {
		float distance = SIGHT_DISTANCE;
		float angle = SIGHT_ANGLE;
	} vision;

};
