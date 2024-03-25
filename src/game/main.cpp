
#include <stdio.h>
#include "app/app.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "glrayfw/core/core.h"


int main( int argc, char** argv )
{
    Logger::getInstance().log(LogLevel::INFO, "GAME START");
	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.
    App app(1280, 720);
    int retval = app.Exec(argc, argv);
    Logger::getInstance().log(LogLevel::INFO, "GAME END");
    return retval;
}
