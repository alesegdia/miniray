
#include "app.h"
#include <glrayfw/render/block.h>
#include "../texgen/canvas.h"
#include "../texgen/color.h"
#include "../texgen/texgen.h"
#include <glrayfw/core/matrix2d.h>
#include "../map/mapgen.h"
#include <glrayfw/entity/entity.h>
#include "../entity/player.h"
#include <glrayfw/physics/layers.h>
#include "../entity/controller/playerhumancontroller.h"
#include <glrayfw/entity/controller/entitycontroller.h>
#include "../entity/controller/mobaicontroller.h"
#include <glrayfw/core/random.h>
#include "../physics/contactlistener.h"
#include <glrayfw/render/scene.h>

App::App::App(int w, int h) : SDLGLApp(w, h)
{

}

App::~App()
{
	Cleanup();
}

void GameScreen::SetupPlayer()
{
	cml::vector2i playerpos = mapdata.rooms[0].RandomPosition( rng, 3 );
	player = this->efactory.SpawnPlayer(playerpos[0], playerpos[1]);
	this->playercontroller = static_cast<PlayerHumanController*>(player->controller);
	efactory.SpawnPortal(playerpos[0], playerpos[1]);
	
}

void GameScreen::Setup(const std::vector<std::string>& args)
{
    uint32_t sid = 0;
	if( args.size() == 2) sid = atoi(args[1].c_str());
	printf("SEED: %d\n",sid);
	rng.seed( sid );


    assets.Prepare( engine()->gl() );

    mapgen::GenRooms( rng, mapdata.config, mapdata.rooms );

    Matrix2D tilemap = mapgen::RasterMapData( mapdata );

    scene.tilemap(tilemap);
	scene.setTextureForTile(1, assets.Texture("TEX_TEX1"));
	scene.setTextureForTile(2, assets.Texture("TEX_TEX2"));
	scene.setTextureForTile(3, assets.Texture("TEX_TEX3"));
	//scene.setTextureForTile(4, assets.Texture(TEX_STAIRS));
	scene.setFloorTexture(assets.Texture("TEX_SUELO"));
	scene.setRoofTexture(assets.Texture("TEX_TECHO"));

    engine()->loadScene(&scene);

	engine()->physics().SetContactListener(new ContactListener());


    efactory.Prepare( &engine()->physics(), &assets, &engine()->emanager(), &engine()->sceneRoot() );

	for (size_t i = 1; i < mapdata.rooms.Size(); i++)
	{
		int lim = rng.uniform(6, 11);
		for (int j = 0; j < lim; j++)
		{
			cml::vector2i enemypos = mapdata.rooms[i].RandomPosition(rng, 1);
			efactory.SpawnEnemy(enemypos[0], enemypos[1]);
		}
	}

	SetupPlayer();

	MobAIController::Prepare( this->player, &(this->efactory) );

}

void GameScreen::Update(uint32_t delta)
{

	if (player->slowdownTimer >= 0)
	{
		engine()->SetSlowDown(0.1f);
	}
	else
	{
		engine()->SetSlowDown(1.0f);
	}

	player->PhysicStep();
	player->Step( delta );
	if (!player->IsAlive())
	{
		RequestExit();
	}

	if (player->parryTimer >= 0)
	{
		assets.Sprite("S3D_ARMA")->SetCurrentFrame(1, 0);
	}
	else
	{
		if (player->attack) assets.Sprite("S3D_ARMA")->SetCurrentFrame(1, 1);
		else assets.Sprite("S3D_ARMA")->SetCurrentFrame(0, 1);
	}

	engine()->renderer().Update();
}

void GameScreen::Render()
{

	if (player->painLastFrame)
	{
		player->painLastFrame = false;
		engine()->renderer().AddShake(0.00015f);
		engine()->renderer().AddRedScreen(0.5f);
	}

	if (player->hpLastFrame)
	{
		player->hpLastFrame = false;
		engine()->renderer().AddGreenScreen(1.0f);
	}

	if (player->ammoLastFrame)
	{
		player->ammoLastFrame = false;
		engine()->renderer().AddOrangeScreen(0.5f);
	}

	engine()->renderer().AddShake(player->skillSet.GetCurrentSkill()->ConsumeShakeLastFrame());

	// SETUP CAMERA
	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
	engine()->cam().position(cml::vector3f(ppos.x, 0, ppos.y));
	engine()->cam().horizontalAngle(-player->GetAngleY());

    engine()->sceneRender(player->GetAngleY());

	RenderWeapon(cml::vector3f(0,0,0));
	RenderMiniText();
	RenderPlayerHP();

	engine()->renderer().SetPlayerHealth(float(player->hp.current) / 100.f);
}

void GameScreen::RenderWeapon(cml::vector3f walkOffset)
{
    engine()->gl()->Disable(GL_DEPTH_TEST);
	cml::matrix44f_c model = cml::identity<4>();
	model = cml::identity<4>();
    cml::vector3f offset(0,0,0);
    offset = cml::rotate_vector( cml::vector3f(0.65,0,0), cml::vector3f(0,1,0), cml::rad(player->GetAngleY()+90) );
	cml::matrix_set_translation( model, player->GetTransform().position + offset + walkOffset );
	cml::matrix_rotate_about_world_y( model, cml::rad(180+player->GetAngleY()) );
	engine()->renderer().RenderSprite3D(assets.Sprite("S3D_ARMA"), model);
}

void GameScreen::RenderMiniText()
{
	uint32_t time = SDL_GetTicks();
	float r = sinf((float(time))/10);
	float g = sinf((float(time))/40);
	float b = sinf((float(time))/400);
    engine()->renderer().renderText("Miniray", -0.35f, 0.7f, cml::vector4f(b,g,r,1));
}

void GameScreen::RenderPlayerHP()
{
    char buf[8];
    sprintf(buf, "%d", player->hp.current);
	float phealth = float(player->hp.current) / float(player->hp.total);
	engine()->renderer().renderText(buf, -1, -0.97f, cml::vector4f(1-phealth,phealth,0,1));

	sprintf(buf, "%d", player->skillSet.GetAmmo());
	engine()->renderer().renderText(buf, 0.7, -0.97f, cml::vector4f(1, 0.5, 0, 1));

	sprintf(buf, "%d", player->skillSet.GetCurrentSlot());
	engine()->renderer().renderText(buf, -0.04f, -0.97f, cml::vector4f(1, 1, 1, 1));

	std::string arma = "";
	switch (player->skillSet.GetCurrentSlot())
	{
	case 1: 
		arma = "pistol";
		break;
	case 2:
		arma = "rifle";
		break;
	case 3:
		arma = "shotgun";
		break;
	case 4:
		arma = "thrower";
		break;
	}
	engine()->renderer().renderText(arma.c_str(), 0.2f, -0.97f, cml::vector4f(1, 1, 1, 1));
}


void GameScreen::HandleEvent(SDL_Event& event)
{
	if( playercontroller->HandleEvent( event ) == 0 )
	{
		switch( event.type )
		{
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_ESCAPE ) RequestExit();
            else if( event.key.keysym.sym == SDLK_p ) engine()->renderer().useDefaultFBO();
            else if( event.key.keysym.sym == SDLK_o ) engine()->renderer().useCreatedFBO();
			break;
		}
	}
}

void GameScreen::Cleanup()
{
}
