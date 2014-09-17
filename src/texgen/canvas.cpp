

#include "canvas.h"

Canvas::Canvas( int w, int h )
{
	data.Alloc( w, h );
}

void Canvas::Plot( int x, int y, Color c )
{
	data.Set( y, x, c );
}

const void* Canvas::Raw()
{
	return data.Raw();
}

void Canvas::Fill( Color c )
{
	data.Set( c );
}


Color HSLtoRGB( Color hsl )
{
	float r, g, b, h, s, l; //this function works with floats between 0 and 1
	float temp1, temp2, tempr, tempg, tempb;
	h = hsl[0] / 256.0;
	s = hsl[1] / 256.0;
	l = hsl[2] / 256.0;

	//If saturation is 0, the color is a shade of grey
	if(s == 0) r = g = b = l;

	//If saturation > 0, more complex calculations are needed
	else
	{
		//set the temporary values
		if(l < 0.5) temp2 = l * (1 + s);
		else temp2 = (l + s) - (l * s);
		temp1 = 2 * l - temp2;
		tempr=h + 1.0 / 3.0;
		if(tempr > 1.0) tempr--;
		tempg=h;
		tempb=h-1.0 / 3.0;
		if(tempb < 0.0) tempb++;

		//red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		//green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g=temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		//blue
		if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
		else if(tempb < 0.5) b = temp2;
		else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
		else b = temp1;
	}

	Color c;
	c[0] = uint8_t(r * 255.0);
	c[1] = uint8_t(g * 255.0);
	c[2] = uint8_t(b * 255.0);
	c[3] = hsl[3];
	return c;
}
