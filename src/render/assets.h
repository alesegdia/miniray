
#pragma once

#include "context.h"
#include "Texture.h"
#include "sprite3d.h"
#include "../constants.h"

constexpr int S3D_BICHO = 		0;
constexpr int S3D_GREENBULLET = 	1;
constexpr int S3D_REDBULLET = 	2;
constexpr int S3D_ARMA = 		3;
constexpr int S3D_PICKSFW = 4;
constexpr int S3D_MAX = 5;

constexpr int TEX_ARMA = 0;
constexpr int TEX_TEX1 = 1;
constexpr int TEX_TEX2 = 2;
constexpr int TEX_TEX3 = 3;
constexpr int TEX_SUELO = 4;
constexpr int TEX_ROBOT = 5;
constexpr int TEX_TECHO = 6;
constexpr int TEX_GREENBULLET = 7;
constexpr int TEX_REDBULLET = 8;
constexpr int TEX_PICKSFW = 9;
constexpr int TEX_MAX = 10;

class Assets {
public:
	~Assets(){
		for( int i = 0; i < TEX_MAX; i++ )
		{
			delete textures[i];
		}
	}
	void Prepare( Render::Context* gl )
	{
		tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile("assets/qwe.png");
		bmp.flipVertically();
		textures[TEX_TEX1] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/asd.png");
		bmp.flipVertically();
		textures[TEX_TEX2] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/asd2.png");
		bmp.flipVertically();
		textures[TEX_TEX3] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/techo.png");
		bmp.flipVertically();
		textures[TEX_TECHO] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/suelo.png");
		bmp.flipVertically();
		textures[TEX_SUELO] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/rob.png");
		bmp.flipVertically();
		textures[TEX_ROBOT] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/bullet.png");
		bmp.flipVertically();
		textures[TEX_GREENBULLET] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/redbullet.png");
		bmp.flipVertically();
		textures[TEX_REDBULLET] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/arma.png");
		bmp.flipVertically();
		textures[TEX_ARMA] = new tdogl::Texture( gl, bmp );

		bmp = tdogl::Bitmap::bitmapFromFile("assets/picksfw.png");
		bmp.flipVertically();
		textures[TEX_PICKSFW] = new tdogl::Texture( gl, bmp );

		sprites[S3D_BICHO].Prepare( gl, textures[TEX_ROBOT], 4, 1 );
		sprites[S3D_BICHO].SetCurrentFrame(2,0);
		sprites[S3D_GREENBULLET].Prepare( gl, textures[TEX_GREENBULLET], 1, 1 );
		sprites[S3D_REDBULLET].Prepare( gl, textures[TEX_REDBULLET], 1, 1 );
		sprites[S3D_ARMA].Prepare( gl, textures[TEX_ARMA], 2, 2 );
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
