
#pragma once


#include <cstdint>
#include <cassert>

class Color
{

private:

	uint8_t data[4];


public:


	Color( uint8_t r=0, uint8_t g=0, uint8_t b=0, uint8_t a = 255 )
	{
		// fully transparent
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
	}

	Color operator+( Color& other )
	{
		Color ret;
		for( int i = 0; i < 4; i++ )
		{
			int tmp = int(data[i]) + int(other.data[i]);
			if( tmp > 255 ) ret.data[i] = 255;
			else ret.data[i] = data[i] + other.data[i];
		}
		return ret;
	}

		/*
		double      hh, p, q, t, ff;
		long        i;
		rgb         out;

		if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
			out.r = in.v;
			out.g = in.v;
			out.b = in.v;
			return out;
		}

		hh = in.h;
		if(hh >= 360.0) hh = 0.0;
		hh /= 60.0;
		i = (long)hh;
		ff = hh - i;
		p = in.v * (1.0 - in.s);
		q = in.v * (1.0 - (in.s * ff));
		t = in.v * (1.0 - (in.s * (1.0 - ff)));

		switch(i) {
		case 0:
			out.r = in.v;
			out.g = t;
			out.b = p;
			break;
		case 1:
			out.r = q;
			out.g = in.v;
			out.b = p;
			break;
		case 2:
			out.r = p;
			out.g = in.v;
			out.b = t;
			break;

		case 3:
			out.r = p;
			out.g = q;
			out.b = in.v;
			break;
		case 4:
			out.r = t;
			out.g = p;
			out.b = in.v;
			break;
		case 5:
		default:
			out.r = in.v;
			out.g = p;
			out.b = q;
			break;
		}
		return out;
		*/

	uint8_t& operator[](size_t index)
	{
		assert(index <= 3);
		return data[index];
	}

};

