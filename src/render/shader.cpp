
#include <stdlib.h>
#include <stdio.h>
#include "shader.h"

const GLenum Shader::dict[] = {
	GL_VERTEX_SHADER,
	GL_FRAGMENT_SHADER,
	GL_GEOMETRY_SHADER
};

Shader::Shader()
{

}

char* filetobuf(const char *file)
{
    FILE *fptr;
    long length;
    char *buf;

    fptr = fopen(file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */

    return buf; /* Return the buffer */
}

bool Shader::LoadFromFile( Render::Context* gl, const char* path, int t )
{
	int isCompiled;
	char* source = filetobuf(path);
	handle = gl->CreateShader( dict[t] );
	gl->ShaderSource( handle, 1, (const GLchar**)&source, 0);
	gl->CompileShader( handle );

	gl->GetShaderiv( handle, GL_COMPILE_STATUS, &isCompiled );
	if( isCompiled == false )
	{
		GLsizei maxLength;
		char* vertexInfoLog;
		gl->GetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

		vertexInfoLog = (char *)malloc(maxLength);

		gl->GetShaderInfoLog(handle, maxLength, &maxLength, vertexInfoLog);

		printf("%s\n", vertexInfoLog);
		free(vertexInfoLog);
		free(source);
		return false;
	}

	free(source);
	return isCompiled;
}

GLuint Shader::Object()
{
	return handle;
}
