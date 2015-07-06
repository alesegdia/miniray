

#pragma once

#include "glcorearb.h"
#include "mesh.h"

class Quad : public Mesh
{

private:

	int width, height;

public:

	Quad() :
		Mesh( AttribConfig::XY_UV )
	{
	}

	// solo se llama una vez para configurar el objeto
	// si se quiere cambiar algo en tiempo de ejecución, habra que implementar algo extra y manejar los vbo para dejarlos actualizados como corresponda
	void Prepare( Render::Context* gl, int width = 1.f, int height = 1.f, float uvx = 1.f, float uvy = 1.f )
	{
		Alloc( 4 );
		UpdateVertices( width, height );
		UpdateUVs( uvx, uvy );

		Mesh::Prepare( gl );
	}

	// recalcula las posiciones de los vértices para un ancho y alto dado
	// se cambia el buffer en ram
	void UpdateVertices( float width, float height )
	{
		this->width = width;
		this->height = height;
		GLfloat* d = vertices;
		d[0] = -width/2; d[1] = -height/2;
		d[2] = -width/2; d[3] = height/2;
		d[4] = width/2; d[5] = -height/2;
		d[6] = width/2; d[7] = height/2;
	}

	// recalcula las uv con un step entre "tiles" de la textura dado
	// se cambia el buffer en ram
	void UpdateUVs( float xstep = 1.f, float ystep = 1.f)
	{
		GLfloat* d = uvs;
		d[0] = 0.f; d[1] = 0.f;
		d[2] = 0.f; d[3] = ystep;
		d[4] = xstep; d[5] = 0.f;
		d[6] = xstep; d[7] = ystep;
	}

};
