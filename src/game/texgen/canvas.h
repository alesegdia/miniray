
#pragma once

#include <glrayfw/render/Bitmap.h>
#include "color.h"

#include <glrayfw/core/matrix2d.h>
#include <glrayfw/core/random.h>

Color HSLtoRGB(Color hsl);

class Canvas
{

    matrix::Matrix2D<Color> data;

public:

	Canvas( int w, int h );

	Canvas& operator=( const Canvas& other )
	{
		data = other.data;
		return *this;
	}

	void Plot( int x, int y, Color c );

	void ToBitmap( tdogl::Bitmap& )
	{

	}

	int Width()
	{
		return data.Cols();
	}

    double SmoothNoise( matrix::Matrix2D<float>& noise, double x, double y )
	{
		double fractX = x - int(x);
		double fractY = y - int(y);

		int x1 = (int(x) + Width()) % Width();
		int y1 = (int(y) + Height()) % Height();
		int x2 = (x1 + Width() - 1) % Width();
		int y2 = (y1 + Height() - 1) % Height();

		double value = 0.0;
		value += fractX		* fractY	 * noise.Get(x1,y1);
		value += fractX		* (1-fractY) * noise.Get(x1,y2);
		value += (1-fractX)	* fractY	 * noise.Get(x2,y1);
		value += (1-fractX)	* (1-fractY) * noise.Get(x2,y2);

		return value;
	}

	Color Get( int x, int y )
	{
		return data.Get( x, y );
	}

	void GenPixelTurbulence( RNG& rng, int light = 64, int rel = 32 )
	{
		GenTurbulence( rng, light, light * rel, false );
	}

    double Turbulence( matrix::Matrix2D<float>& noise, double x, double y, double size, bool bifilter = true, double base = 128.0 )
	{
		double value = 0.0, initialSize = size;
		while( size >= 1 )
		{
			if( bifilter ) value += SmoothNoise( noise, x / size, y / size ) * size;
			else value += noise.Get(x/size,y/size);
			size /= 2.0;
		}

		return (base * value / initialSize);
	}

	void Add( Canvas& other )
	{
		//assert( other.Width() == Width() && other.Height() == Height() );
		for( int x = 0; x < Width(); x++ )
		for( int y = 0; y < Height(); y++ )
		{
			Color me = data.Get(y,x);
			Color it = other.data.Get(y,x);
			data.Set(y,x,me+it);
		}
	}

    void MakeNoise( matrix::Matrix2D<float>& noise, RNG& rng, int w, int h )
	{
		for( int x = 0; x < w; x++ )
		for( int y = 0; y < h; y++ )
		{
			noise.Set(x,y,rng.uniform());
		}
	}

	void GenTurbulence( RNG& rng, double zoom = 64, double base = 128, bool smooth = true )
	{
		Canvas* c = this;
		int w, h;
		w = Width();
		h = Height();

        matrix::Matrix2D<float> noise(w, h);
		MakeNoise( noise, rng, w, h );

		for( int x = 0; x < w; x++ )
		for( int y = 0; y < h; y++ )
		{
			uint8_t val = ((uint8_t)(Turbulence( noise, x, y, zoom, smooth, base )));
			c->Plot( x, y, Color(val, val, val, 255 ) );
		}
	}

	void GenClouds( RNG& rng, double Ldiv = 3, double zoom = 64, uint8_t H = 169, uint8_t S = 255, int base = 192 )
	{
		Canvas* c = this;
		int w, h;
		w = Width();
		h = Height();

        matrix::Matrix2D<float> noise(w, h);
		MakeNoise( noise, rng, w, h );


		for( int x = 0; x < w; x++ )
		for( int y = 0; y < h; y++ )
		{
			int L = base + uint8_t(Turbulence( noise, x, y, zoom, true )) / Ldiv;
			if( L > 255 ) L = 255;
			c->Plot( x, y, HSLtoRGB( Color( H, S, L, 255 ) ) );
			//uint8_t val = ((uint8_t)(Turbulence( noise, x, y, zoom, false )));
			//c->Plot( x, y, Color(val, val, val, 255 ) );
		}

	}


	int Height()
	{
		return data.Rows();
	}

	const void* Raw();
	void Fill( Color c );
};
