
#ifndef __SHAD__
#define __SHAD__

#include "context.h"
#include "glcorearb.h"
char* filetobuf(const char *file);

class Shader
{

public:

	const static int VERTEX = 0;
	const static int FRAGMENT = 1;
	const static int GEOMETRY = 2;


private:

	static const GLenum dict[];

	GLuint handle;


public:

	Shader(  );

	bool LoadFromFile( Render::Context* gl, const char* path, int t );
	GLuint Object();


};



#endif
