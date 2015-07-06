
#pragma once

//#include <freetype2/config/ftheader.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "program.h"
#include <glrayfw/render/context.h>

class Font {
public:


	void Prepare( Render::Context* gl, FT_Library& ft, const char* path, int height=48 )
	{
		if(FT_New_Face(ft, path, 0, &face)) fprintf(stderr, "Could not open font\n");
		SetSize(height);

		FT_GlyphSlot g = face->glyph;
		w = h = 0;
		int roww = 0;
		int rowh = 0;
		for( int i = 32; i < 128; i++ )
		{
			if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", i);
				continue;
			}
			roww += g->bitmap.width+1;
			rowh = (rowh>g->bitmap.rows)?rowh:g->bitmap.rows;
		}
		w = roww;
		h = rowh;

		gl->ActiveTexture(GL_TEXTURE0);
		gl->GenTextures(1,&tex);
		gl->BindTexture(GL_TEXTURE_2D, tex);
		gl->Uniform1i( uniform_tex, 0 );

		gl->BlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
		gl->TexImage2D(GL_TEXTURE_2D, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
		gl->PixelStorei(GL_UNPACK_ALIGNMENT, 1);

		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int ox = 0;
		int oy = 0;
		rowh = 0;
		for( int i = 32; i < 128; i++ )
		{
			if( FT_Load_Char( face, i, FT_LOAD_RENDER ) ) {
				printf("ERROR!!");
				continue;
			}

			gl->TexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

			c[i].ax = g->advance.x >> 6;
			c[i].ay = g->advance.y >> 6;

			c[i].bw = g->bitmap.width;
			c[i].bh = g->bitmap.rows;

			c[i].bl = g->bitmap_left;
			c[i].bt = g->bitmap_top;

			c[i].tx = (float)ox / (float)w;
			c[i].ty = 0;

			rowh = std::max( rowh, (int) g->bitmap.rows );
			ox += g->bitmap.width+1;
		}

		FT_Done_Face(face);

	}


	int UpdateGPUQuads( Render::Context* gl, const char* text, float x, float y, float sx, float sy )
	{
		struct point {
			GLfloat x;
			GLfloat y;
			GLfloat s;
			GLfloat t;
		} coords[6 * strlen(text)];

		int n = 0;
		for(const char *p = text; *p; p++) {
			float x2 =  x + c[*p].bl * sx;
			float y2 = -y - c[*p].bt * sy;
			float w = c[*p].bw * sx;
			float h = c[*p].bh * sy;

			/* Advance the cursor to the start of the next character */
			x += c[*p].ax * sx;
			y += c[*p].ay * sy;

			/* Skip glyphs that have no pixels */
			if(!w || !h)
			{
				continue;
			}

			float cpbh = c[*p].bh;
			float cptx = c[*p].tx, cpbw = c[*p].bw;
			coords[n++] = (point) {
				x2 + w, -y2, c[*p].tx + c[*p].bw / this->w, 0};
			coords[n++] = (point) {
				x2, -y2, c[*p].tx, 0};
			coords[n++] = (point) {
				x2, -y2 - h, c[*p].tx, cpbh/this->h};
			coords[n++] = (point) {
				x2 + w, -y2, c[*p].tx + c[*p].bw / this->w , 0};
			coords[n++] = (point) {
				x2, -y2 - h, c[*p].tx, cpbh/this->h};
			coords[n++] = (point) {
				x2 + w, -y2 - h, c[*p].tx + c[*p].bw / this->w , cpbh/this->h};

		}
		gl->BufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
		return n;
	}

	GLuint Texture() { return tex; }

private:

	void SetSize( int size )
	{
		FT_Set_Pixel_Sizes( face, 0, size );
	}


	FT_Face face;
	GLuint tex;
	GLuint attribute_coord, uniform_tex;
	int w, h;

	struct character_info {
		float ax; // advance.x
		float ay; // advance.y
		float bw; // bitmap.width;
		float bh; // bitmap.rows;
		float bl; // bitmap_left;
		float bt; // bitmap_top;
		float tx; // x offset of glyph in texture coordinates
		float ty; // y offset of glyph in texture coordinates
	} c[128];



};

