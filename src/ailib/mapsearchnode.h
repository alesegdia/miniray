
#pragma once

#include "../map/map.h"
#include "stlastar.h"

class MapSearchNode {
private:
	static Map map;

public:
	static SetMap( Map* pmap )
	{
		MapSearchNode::map = pmap;
	}
	int x,y;

	MapSearchNode() { x=y=0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }

	static int GetMap( int x, int y )
	{
		if( x < 0 || x >= map.Width() || y < 0 || y >= map.Height() )
		{
			return 9;
		}
		return map.Get( x, y );
	}

	float GoalDistanceEstimate( MapSearchNode& nodeGoal )
	{
		float xd = float( ( (float)x - (float)nodeGoal.x ) );
		float yd = float( ( (float)y - (float)nodeGoal.y) );

		return xd + yd;
	}

	bool IsGoal( MapSearchNode& nodeGoal )
	{
		return (x == nodeGoal.x) && (y == nodeGoal.y);
	}

#define DISPATCH_SUCC(x__,y__) \
	if( (GetMap(x__,y__) < 9) && !((parent_x == x__) && (parent_y == y__)) ) \
	{ newNode = MapSearchNode( x__, y__ ); astarsearch->AddSuccessor( newNode );

	bool GetSuccessors( AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node )
	{
		int parent_x = -1;
		int parent_y = -1;

		if( parent_node )
		{
			parent_x = parent_node->x;
			parent_y = parent_node->y;
		}

		MapSearchNode newNode;

		DISPATCH_SUCC( x-1, y );
		DISPATCH_SUCC( x-1, y-1 );
		DISPATCH_SUCC( x, y-1 );
		DISPATCH_SUCC( x+1, y-1 );
		DISPATCH_SUCC( x+1, y );
		DISPATCH_SUCC( x+1, y+1 );
		DISPATCH_SUCC( x, y+1 );
		DISPATCH_SUCC( x-1, y+1 );

		return true;
	}

	float GetCost( MapSearchNode& successor )
	{
		return (float) GetMap( x, y );
	}

	bool IsSameState( MapSearchNode& rhs )
	{
		// same state in a maze search is simply when (x,y) are the same
		if( (x == rhs.x) &&
			(y == rhs.y) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void PrintNodeInfo()
	{
		char str[100];
		sprintf( str, "Node position : (%d,%d)\n", x,y );
		cout << str;
	}

};

