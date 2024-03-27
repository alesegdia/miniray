#pragma once

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
private:
	void BeginContact( b2Contact* contact ) override;
	void EndContact( b2Contact* contact ) override;
};
