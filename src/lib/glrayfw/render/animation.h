
#pragma once

#include "../core/dynamicarray.h"

class Animation {
public:

	struct Frame
	{
		int num;
		int time;
	};

	struct Data
	{
		int current;
		int num_plays;
		uint32_t next_frame;
	};

	Animation () {}
	virtual ~Animation () {}

	int GetFrame( const Data& d )
	{
		return 0;
	}

	void Update( Data& d )
	{
		bool active = true;
		uint32_t now = SDL_GetTicks();
		bool active = d.num_plays != 0;
		if( d.num_plays > 0 && d.current == frames.Size() - 1 && d.next_frame < now )
		{
			d.num_plays--;
		}

		if( active )
		{
			if( d.next_frame < now )
			{
				d.current = (d.current+1) % frames.Size();
				d.next_frame = now + frames[d.current].time;
			}
		}

	}

	void AddFrame( const Frame& f )
	{
		frames.Add( f );
	}

private:

	DynamicArray<Frame> frames;

};

