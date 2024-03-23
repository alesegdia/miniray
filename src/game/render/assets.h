
#pragma once

#include <glrayfw/render/context.h>
#include <glrayfw/render/Texture.h>
#include <glrayfw/render/sprite3d.h>
#include <unordered_map>

#include "../constants.h"


class Assets {
public:
	~Assets(){
		for (auto item : m_textures)
		{
			delete item.second;
		}

		for (auto item : m_sprites)
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

	void LoadSprite(Render::Context* gl, const char* id, std::string texid, int w = 1, int h = 1)
	{
		Sprite3D* sprite = new Sprite3D();
		assert(m_textures[texid] != nullptr);
		sprite->Prepare(gl, m_textures[texid], w, h);
		m_sprites[id] = sprite;
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
		LoadTexture(gl, "assets/bluebullet.png", "TEX_BLUEBULLET");
		LoadTexture(gl, "assets/bulletold.png", "TEX_BULLETOLD");
		LoadTexture(gl, "assets/arma.png", "TEX_ARMA");
		LoadTexture(gl, "assets/picksfw.png", "TEX_PICKSFW");
		LoadTexture(gl, "assets/pickhp.png", "TEX_PICKHP");
		LoadTexture(gl, "assets/fireball.png", "TEX_FIREBALL");
		LoadTexture(gl, "assets/stairs.png", "TEX_STAIRS");

		LoadSprite(gl, "S3D_ROBOT", "TEX_ROBOT", 4, 3);
		m_sprites["S3D_ROBOT"]->SetCurrentFrame(0, 0);
		
		LoadSprite(gl, "S3D_GREENBULLET", "TEX_GREENBULLET");
		LoadSprite(gl, "S3D_REDBULLET", "TEX_REDBULLET");
		LoadSprite(gl, "S3D_BLUEBULLET", "TEX_BLUEBULLET");
		LoadSprite(gl, "S3D_ARMA", "TEX_ARMA", 2, 2);
		LoadSprite(gl, "S3D_FIREBALL", "TEX_FIREBALL");
		LoadSprite(gl, "S3D_PICKSFW", "TEX_PICKSFW");
		LoadSprite(gl, "S3D_PICKHP", "TEX_PICKHP");
		LoadSprite(gl, "S3D_BULLETOLD", "TEX_BULLETOLD");
	}

	Sprite3D* Sprite( std::string id )
	{
		return m_sprites[id];
	}

	tdogl::Texture* Texture( const std::string& texID )
	{
		return m_textures[texID];
	}

private:

	std::unordered_map<std::string, Sprite3D*> m_sprites;
	std::unordered_map<std::string, tdogl::Texture*> m_textures;


};
