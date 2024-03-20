
#pragma once

#include <glrayfw/render/context.h>
#include <glrayfw/render/Texture.h>
#include <glrayfw/render/sprite3d.h>
#include "../constants.h"

const int S3D_BICHO = 		0;
const int S3D_GREENBULLET = 	1;
const int S3D_REDBULLET = 	2;
const int S3D_ARMA = 		3;
const int S3D_PICKSFW = 4;
const int S3D_FIREBALL = 5;
const int S3D_MAX = 6;

const int TEX_ARMA = 0;
const int TEX_TEX1 = 1;
const int TEX_TEX2 = 2;
const int TEX_TEX3 = 3;
const int TEX_SUELO = 4;
const int TEX_ROBOT = 5;
const int TEX_TECHO = 6;
const int TEX_GREENBULLET = 7;
const int TEX_REDBULLET = 8;
const int TEX_PICKSFW = 9;
const int TEX_FIREBALL = 10;
const int TEX_STAIRS = 11;
const int TEX_MAX = 12;

class Assets {
public:
	~Assets(){
		for( int i = 0; i < TEX_MAX; i++ )
		{
			delete textures[i];
		}
	}

	void LoadTexture( Render::Context* gl, const char* path, int texid )
	{
		tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(path);
		bmp.flipVertically();
		textures[texid] = new tdogl::Texture( gl, bmp );
	}

	void Prepare( Render::Context* gl )
	{
		LoadTexture( gl, "assets/qwe.png", TEX_TEX1 );
		LoadTexture( gl, "assets/asd.png", TEX_TEX2 );
		LoadTexture( gl, "assets/asd2.png", TEX_TEX3 );
		LoadTexture( gl, "assets/techo.png", TEX_TECHO );
		LoadTexture( gl, "assets/suelo.png", TEX_SUELO );
		LoadTexture( gl, "assets/rob.png", TEX_ROBOT );
		LoadTexture( gl, "assets/bullet.png", TEX_GREENBULLET );
		LoadTexture( gl, "assets/redbullet.png", TEX_REDBULLET );
		LoadTexture( gl, "assets/arma.png", TEX_ARMA );
		LoadTexture( gl, "assets/picksfw.png", TEX_PICKSFW );
		LoadTexture( gl, "assets/fireball.png", TEX_FIREBALL );
		LoadTexture( gl, "assets/stairs.png", TEX_STAIRS);

		sprites[S3D_BICHO].Prepare( gl, textures[TEX_ROBOT], 4, 3 );
		sprites[S3D_BICHO].SetCurrentFrame(0,0);
		sprites[S3D_GREENBULLET].Prepare( gl, textures[TEX_GREENBULLET], 1, 1 );
		sprites[S3D_REDBULLET].Prepare( gl, textures[TEX_REDBULLET], 1, 1 );
		sprites[S3D_ARMA].Prepare( gl, textures[TEX_ARMA], 2, 2 );
		sprites[S3D_FIREBALL].Prepare( gl, textures[TEX_FIREBALL], 1, 1 );
		sprites[S3D_PICKSFW].Prepare( gl, textures[TEX_PICKSFW], 1, 1 );
	}

	Sprite3D* Sprite( int spriteid )
	{
		return sprites + spriteid;
	}

	tdogl::Texture* Texture( int textureid )
	{
		return *(textures + textureid);
	}

private:

	Sprite3D sprites[S3D_MAX];
	tdogl::Texture* textures[TEX_MAX];


};
