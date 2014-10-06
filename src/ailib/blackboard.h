
#pragma once

#include "stlastar.h"
#include "../core/matrix2d.h"


class Blackboard {
public:
	Matrix2D<float> sharedmap;
	AStarSearch<MapSearchNode> astarsearch;
	Player* player;

};



