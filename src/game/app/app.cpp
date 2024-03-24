
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

void App::SetupPlayer()
{
	cml::vector2i playerpos = mapdata.rooms[0].RandomPosition( rng, 3 );
	player = this->efactory.SpawnPlayer(playerpos[0], playerpos[1]);
	this->playercontroller = static_cast<PlayerHumanController*>(player->controller);
}

void App::Setup(int argc, char** argv)
{
    uint32_t sid = 0;
	if( argc == 2 ) sid = atoi(argv[1]);
	printf("SEED: %d\n",sid);
	rng.seed( sid );


    assets.Prepare( GL() );

    mapgen::GenRooms( rng, mapdata.config, mapdata.rooms );

    Matrix2D tilemap = mapgen::RasterMapData( mapdata );

    scene.tilemap(tilemap);
	scene.setTextureForTile(1, assets.Texture("TEX_TEX1"));
	scene.setTextureForTile(2, assets.Texture("TEX_TEX2"));
	scene.setTextureForTile(3, assets.Texture("TEX_TEX3"));
	//scene.setTextureForTile(4, assets.Texture(TEX_STAIRS));
	scene.setFloorTexture(assets.Texture("TEX_SUELO"));
	scene.setRoofTexture(assets.Texture("TEX_TECHO"));

    loadScene(&scene);

	physics().SetContactListener(new ContactListener());


    efactory.Prepare( &physics(), &assets, &entityManager(), &sceneRoot() );

	for( size_t i = 1; i < mapdata.rooms.Size(); i++ )
	{
		int lim = rng.uniform(6,11);
		for( int j = 0; j < lim; j++ )
		{
			cml::vector2i enemypos = mapdata.rooms[i].RandomPosition( rng, 1 );
			efactory.SpawnEnemy( enemypos[0], enemypos[1] );
		}
	}

	SetupPlayer();

	MobAIController::Prepare( this->player, &(this->efactory) );

}

void App::Update(uint32_t delta)
{

	if (player->slowdownTimer >= 0)
	{
		SetSlowDown(0.1f);
	}
	else
	{
		SetSlowDown(1.0f);
	}

	player->PhysicStep();
	player->Step( delta );
	if (!player->IsAlive())
	{
		Stop();
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

	deltatime = delta;

	renderer().Update();
}

void App::Render()
{

	if (player->painLastFrame)
	{
		player->painLastFrame = false;
		renderer().AddShake(0.00015f);
		renderer().AddRedScreen(0.5f);
	}

	if (player->hpLastFrame)
	{
		player->hpLastFrame = false;
		renderer().AddGreenScreen(1.0f);
	}

	if (player->ammoLastFrame)
	{
		player->ammoLastFrame = false;
		renderer().AddOrangeScreen(0.5f);
	}

	renderer().AddShake(player->skillSet.GetCurrentSkill()->ConsumeShakeLastFrame());

	// SETUP CAMERA
	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
    cam().position(cml::vector3f(ppos.x, 0, ppos.y));
    cam().horizontalAngle(-player->GetAngleY());

    sceneRender(player->GetAngleY());

	RenderWeapon(cml::vector3f(0,0,0));
	RenderMiniText();
	RenderPlayerHP();

	renderer().SetPlayerHealth(float(player->hp.current) / 100.f);
}

void App::RenderWeapon(cml::vector3f walkOffset)
{
    GL()->Disable(GL_DEPTH_TEST);
	cml::matrix44f_c model = cml::identity<4>();
	model = cml::identity<4>();
    cml::vector3f offset(0,0,0);
    offset = cml::rotate_vector( cml::vector3f(0.65,0,0), cml::vector3f(0,1,0), cml::rad(player->GetAngleY()+90) );
	cml::matrix_set_translation( model, player->GetTransform().position + offset + walkOffset );
	cml::matrix_rotate_about_world_y( model, cml::rad(180+player->GetAngleY()) );
	renderer().RenderSprite3D(assets.Sprite("S3D_ARMA"), model);
}

void App::RenderMiniText()
{
	uint32_t time = SDL_GetTicks();
	float r = sinf((float(time))/10);
	float g = sinf((float(time))/40);
	float b = sinf((float(time))/400);
    renderer().renderText("Miniray", -0.35f, 0.7f, cml::vector4f(b,g,r,1));
}

void App::RenderPlayerHP()
{
    char buf[8];
    sprintf(buf, "%d", player->hp.current);
	float phealth = float(player->hp.current) / float(player->hp.total);
	renderer().renderText(buf, -1, -0.97f, cml::vector4f(1-phealth,phealth,0,1));

	sprintf(buf, "%d", player->skillSet.GetAmmo());
	renderer().renderText(buf, 0.7, -0.97f, cml::vector4f(1, 0.5, 0, 1));

	sprintf(buf, "%d", player->skillSet.GetCurrentSlot());
	renderer().renderText(buf, -0.04f, -0.97f, cml::vector4f(1, 1, 1, 1));

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
	renderer().renderText(arma.c_str(), 0.2f, -0.97f, cml::vector4f(1, 1, 1, 1));
}


void App::HandleEvent(SDL_Event& event)
{
	if( playercontroller->HandleEvent( event ) == 0 )
	{
		switch( event.type )
		{
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_ESCAPE ) Stop();
            else if( event.key.keysym.sym == SDLK_p ) renderer().useDefaultFBO();
            else if( event.key.keysym.sym == SDLK_o ) renderer().useCreatedFBO();
			break;
		}
	}
}

void App::Cleanup()
{
}
