
#pragma once
#include "glcorearb.h"
#include "mesh.h"

class Block : public Mesh
{

public:

	static const GLfloat vert[];
	static const GLfloat colors[];
	static const GLfloat norm[];

	Block() :
		Mesh( AttribConfig::XYZUV_INST )
	{
	}

	void Prepare( Render::Context* gl )
	{
		const float blockvert[] = {

			//  X     Y     Z       U     V
			// bottom
			-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

			// top
			-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

			// front
			-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

			// back
			-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

			// left
			-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

			// right
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 1.0f
		};

		Alloc( 36 );
		LoadBuffer( vertices, blockvert, 5 );

		Mesh::Prepare( gl );
	}

};

