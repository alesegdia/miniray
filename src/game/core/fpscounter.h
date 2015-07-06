
#pragma once

#include <stdio.h>

template <typename T>
class FPSCounter
{

private:

	T milis;
	int frames;
	int FPS;


public:

	FPSCounter()
	{
		FPS = frames= milis = 0;
	}

	void Tick( T time )
	{
		if( time - milis >= 1000 )
		{
			FPS = frames;
			frames = 0;
			milis = time;
		}
		frames++;
	}

	int GetFPS()
	{
		return FPS;
	}

};
