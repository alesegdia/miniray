
#pragma once


#include <cml/cml.h>
#include "context.h"
#include "Texture.h"
#include "quad.h"
#include "block.h"
#include "sprite3d.h"
#include "program.h"
#include "../entity/entity.h"
#include "plane.h"
#include "../constants.h"

class Renderer
{

private:

	cml::matrix44f_c view;
	cml::matrix44f_c projection;


	float sprite3d_fog_range;
	float cube_fog_range;

	Render::Context* gl;
	Program quadprog, blockprog, planeprog;


	Block block;


public:

	void Prepare( Render::Context* gl )
	{
		this->gl = gl;

		blockprog.Prepare( gl, "data/vs_mvptex_inst.vert", "data/fs_mvptex_inst.frag" );
		quadprog.Prepare( gl, "data/vs_quadanim.vert", "data/fs_quadanim.frag" );
		planeprog.Prepare( gl, "data/vs_plane.vert", "data/fs_plane.frag" );

		GLuint pos_loc = 0;
		GLuint tex_loc = 1;
		GLuint model_loc = 2;

		blockprog.BindAttribLocation( gl, tex_loc, "in_TexCoord" );
		blockprog.BindAttribLocation( gl, pos_loc, "in_Position" );
		blockprog.BindAttribLocation( gl, model_loc, "in_ModelMatrix" );

		quadprog.BindAttribLocation( gl, tex_loc, "in_TexCoord" );
		quadprog.BindAttribLocation( gl, pos_loc, "in_Position" );

		block.Prepare( gl );

		gl->Enable(GL_CULL_FACE);
		gl->Enable(GL_DEPTH_TEST);
		gl->DepthFunc(GL_LEQUAL);
		gl->CullFace( GL_FRONT );
		gl->FrontFace( GL_CW );
		gl->Enable (GL_BLEND);
		gl->BlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//gl->BlendFunc (GL_ONE, GL_ONE);
	}

	void RenderClear()
	{
		gl->ClearColor(0.0, 0.0, 0.0, 1.0);
		gl->Clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	inline void BindVP( GLuint shaderprogram )
	{
		gl->UniformMatrix4fv( gl->GetUniformLocation( shaderprogram, "view" ), 1, false, view.data() );
		gl->UniformMatrix4fv( gl->GetUniformLocation( shaderprogram, "proj" ), 1, false, projection.data() );
	}

	inline void BindVisionRange( GLuint shaderprogram )
	{
		gl->Uniform1f( gl->GetUniformLocation( shaderprogram, "range" ), PLAYER_VISION_RANGE );
	}

	void RenderMap( Map& map, tdogl::Texture* tex1, tdogl::Texture* tex2, tdogl::Texture* tex3 )
	{
		GLuint shaderprogram = blockprog.Object();
		gl->UseProgram( shaderprogram );
		BindVP( shaderprogram );
		BindVisionRange( shaderprogram );

		GLuint VAO = block.GetVAO();
		gl->BindVertexArray(VAO);
			RenderBlocks( map, tex1, 1 );
			RenderBlocks( map, tex2, 2 );
			RenderBlocks( map, tex3, 3 );
		gl->BindVertexArray(0);
	}

	void BatchSprite3D()
	{
		GLuint shaderprogram = quadprog.Object();
		gl->UseProgram( shaderprogram );
		BindVP( shaderprogram );
		BindVisionRange( shaderprogram );
	}

	void RenderSprite3D( Sprite3D& sprite, const cml::matrix44f_c& model )
	{
		cml::vector2f f = sprite.CurrentFrame();
		cml::vector2f s = sprite.FrameSize();
		gl->BindVertexArray( sprite.GetQuad().GetVAO() );
			gl->UniformMatrix4fv( gl->GetUniformLocation( quadprog.Object(), "model" ), 1, false, model.data() );//sprite.GetModel().data() );
			gl->Uniform2f( gl->GetUniformLocation( quadprog.Object(), "frame" ), f[0], f[1] );
			gl->Uniform2f( gl->GetUniformLocation( quadprog.Object(), "size" ), s[0], s[1] );
			gl->ActiveTexture( GL_TEXTURE0 );
			gl->BindTexture( GL_TEXTURE_2D, sprite.GetTex()->object() );
			gl->Uniform1i( gl->GetUniformLocation( quadprog.Object(), "tex" ), 0 );
			gl->DrawArrays( GL_TRIANGLE_STRIP, 0, sprite.GetQuad().NumElements() );
		gl->BindVertexArray(0);
	}

	void RenderPlane( Plane* p, const cml::matrix44f_c& model, tdogl::Texture* tex )
	{
		GLuint shaderprogram = planeprog.Object();
		gl->UseProgram( shaderprogram );
		BindVP( shaderprogram );
		BindVisionRange( shaderprogram );

		gl->BindVertexArray( p->GetVAO() );
			gl->UniformMatrix4fv( gl->GetUniformLocation( planeprog.Object(), "view" ), 1, false, view.data() );
			gl->UniformMatrix4fv( gl->GetUniformLocation( planeprog.Object(), "proj" ), 1, false, projection.data() );
			gl->UniformMatrix4fv( gl->GetUniformLocation( planeprog.Object(), "model" ), 1, false, model.data() );
			gl->ActiveTexture( GL_TEXTURE0 );
			gl->BindTexture( GL_TEXTURE_2D, tex->object() );
			gl->Uniform1i( gl->GetUniformLocation( planeprog.Object(), "tex" ), 0 );
			gl->DrawArrays( GL_TRIANGLES, 0, p->NumElements() );
		gl->BindVertexArray(0);
	}

	void RenderEntity( Entity* ent )
	{
		gl->UseProgram( quadprog.Object() );

		Sprite3D* sprite = ent->GetSprite();
		cml::vector2f f = sprite->CurrentFrame();
		cml::vector2f s = sprite->FrameSize();
		gl->BindVertexArray( sprite->GetQuad().GetVAO() );
			gl->UniformMatrix4fv( gl->GetUniformLocation( quadprog.Object(), "model" ), 1, false, ent->Model().data() );//sprite.GetModel().data() );
			gl->Uniform2f( gl->GetUniformLocation( quadprog.Object(), "frame" ), f[0], f[1] );
			gl->Uniform2f( gl->GetUniformLocation( quadprog.Object(), "size" ), s[0], s[1] );
			gl->ActiveTexture( GL_TEXTURE0 );
			gl->BindTexture( GL_TEXTURE_2D, sprite->GetTex()->object() );
			gl->Uniform1i( gl->GetUniformLocation( quadprog.Object(), "tex" ), 0 );
			gl->DrawArrays( GL_TRIANGLE_STRIP, 0, sprite->GetQuad().NumElements() );
		gl->BindVertexArray(0);
	}


	void RenderFinish( SDL_Window* mainWindow )
	{
		SDL_GL_SwapWindow(mainWindow);
	}

	void RenderBlocks( Map& map, tdogl::Texture* tex, int num )
	{
		GLuint shaderprogram = blockprog.Object();
		gl->ActiveTexture(GL_TEXTURE0);
		gl->BindTexture(GL_TEXTURE_2D, tex->object());
		gl->Uniform1i( gl->GetUniformLocation( shaderprogram, "tex" ), 0 );
		map.GenerateModels(num);
		GLvoid* cpu_model_buffer = ( (GLvoid*) map.GetModelsBuffer() );
		gl->BindBuffer(GL_ARRAY_BUFFER, block.GetVBO(1));
		gl->BufferData( GL_ARRAY_BUFFER, sizeof(cml::matrix44f_c) * map.GetModelsNum(), cpu_model_buffer, GL_STATIC_DRAW);
		gl->DrawArraysInstanced( GL_TRIANGLES, 0, block.NumElements(), map.GetModelsNum() );
	}


	void SetVP( const cml::matrix44f_c& view, const cml::matrix44f_c& projection )
	{
		this->view = view;
		this->projection = projection;
	}


	void Dispose()
	{
		quadprog.Dispose( gl );
		blockprog.Dispose( gl );
		block.Dispose( gl );
	}

};
