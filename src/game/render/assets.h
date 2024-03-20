
#pragma once

#include <glrayfw/render/context.h>
#include <glrayfw/render/Texture.h>
#include <glrayfw/render/sprite3d.h>
#include <unordered_map>

#include "../constants.h"

const int S3D_BICHO = 		0;
const int S3D_GREENBULLET = 	1;
const int S3D_REDBULLET = 	2;
const int S3D_ARMA = 		3;
const int S3D_PICKSFW = 4;
const int S3D_FIREBALL = 5;
const int S3D_MAX = 6;


class Assets {
public:
	~Assets(){
		for (auto item : m_textures)
		{
			delete item.second;
		}
	}

	void LoadTexture( Render::Context* gl, const char* path, const char* id )
	{
		tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(path);
		bmp.flipVertically();
		m_textures[id] = new tdogl::Texture( gl, bmp );
	}

	void Prepare( Render::Context* gl )
	{
		LoadTexture(gl, "assets/qwe.png", "TEX_TEX1");
		LoadTexture(gl, "assets/asd.png", "TEX_TEX2");
		LoadTexture(gl, "assets/asd2.png", "TEX_TEX3");
		LoadTexture(gl, "assets/techo.png", "TEX_TECHO");
		LoadTexture(gl, "assets/suelo.png", "TEX_SUELO");
		LoadTexture(gl, "assets/rob.png", "TEX_ROBOT");
		LoadTexture(gl, "assets/bullet.png", "TEX_GREENBULLET");
		LoadTexture(gl, "assets/redbullet.png", "TEX_REDBULLET");
		LoadTexture(gl, "assets/arma.png", "TEX_ARMA");
		LoadTexture(gl, "assets/picksfw.png", "TEX_PICKSFW");
		LoadTexture(gl, "assets/fireball.png", "TEX_FIREBALL");
		LoadTexture(gl, "assets/stairs.png", "TEX_STAIRS");

		sprites[S3D_BICHO].Prepare(gl, m_textures["TEX_ROBOT"], 4, 3);
		sprites[S3D_BICHO].SetCurrentFrame(0,0);
		sprites[S3D_GREENBULLET].Prepare(gl, m_textures["TEX_GREENBULLET"], 1, 1);
		sprites[S3D_REDBULLET].Prepare(gl, m_textures["TEX_REDBULLET"], 1, 1);
		sprites[S3D_ARMA].Prepare(gl, m_textures["TEX_ARMA"], 2, 2);
		sprites[S3D_FIREBALL].Prepare(gl, m_textures["TEX_FIREBALL"], 1, 1);
		sprites[S3D_PICKSFW].Prepare(gl, m_textures["TEX_PICKSFW"], 1, 1);
	}

	Sprite3D* Sprite( int spriteid )
	{
		return sprites + spriteid;
	}

	tdogl::Texture* Texture( const std::string& texID )
	{
		return m_textures[texID];
	}

private:

	Sprite3D sprites[S3D_MAX];
	std::unordered_map<std::string, tdogl::Texture*> m_textures;


};
