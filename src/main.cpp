
#include <stdio.h>
#include "app/app.h"
#include <iostream>
#include <Box2D/Box2D.h>


int main( int argc, char** argv )
{

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return App().Exec(argc, argv);
}
