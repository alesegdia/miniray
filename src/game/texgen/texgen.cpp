
#include "texgen.h"
#include <glrayfw/core/random.h>
#include "color.h"

namespace rzfx
{

RNG rng;

void noise( Canvas& c, uint8_t r, uint8_t g, uint8_t b )
{
	for( int x = 0; x < c.Width(); x++ )
	for( int y = 0; y < c.Height(); y++ )
	{
		float u = rng.uniform();
		c.Plot( x, y, Color(uint8_t(u*r),uint8_t(u*g),uint8_t(u*b)) );
	}
}

Color smooth( Canvas& c, double x, double y )
{
	double fractX = x - int(x);
	double fractY = y - int(y);

	int x1 = (int(x) + c.Width()) % c.Width();
	int y1 = (int(y) + c.Height()) % c.Height();
	int x2 = (x1 + c.Width() - 1) % c.Width();
	int y2 = (y1 + c.Height() - 1) % c.Height();

	Color col;
	for( int i = 0; i < 3; i++ )
	{
		double value = 0.0;
		value += fractX		* fractY	 * c.Get(x1,y1)[i];
		value += fractX		* (1-fractY) * c.Get(x1,y2)[i];
		value += (1-fractX)	* fractY	 * c.Get(x2,y1)[i];
		value += (1-fractX)	* (1-fractY) * c.Get(x2,y2)[i];
		col[i] = uint8_t(value);
	}

	return col;
}

#define ASSERT_CANVAS(c1,c2) assert( c1 != c2 && c1.Width() == c2.Width() && c1.Height() == c2.Height() ) 

Canvas turbulence( Canvas& in, Canvas& out )
{
	Canvas cv(in.Width(),in.Height());
	//ASSERT_CANVAS(in,out);

	for( int x = 0; x < in.Width(); x++ )
	for( int y = 0; y < in.Height(); y++ )
	{
		//uint8_t val = ((uint8_t)(turbulence(in,x,y,zoom,smooth,base)));
	}
	return cv;
}

}
