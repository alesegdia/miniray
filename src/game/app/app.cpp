
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

App::App() :
	SDLGLApp( 800, 600 )
{
}

void App::SetupPlayer()
{
	cml::vector2i playerpos = mapdata.rooms[0].RandomPosition( rng, 3 );
	player = this->efactory.SpawnPlayer(playerpos[0], playerpos[1]);
	this->playercontroller = static_cast<PlayerHumanController*>(player->controller);
}

void App::Setup(int argc, char** argv)
{
	//map.LoadFromFile( "mimapa.txt" );
	//map.Debug();

	SDL_ShowCursor(0);
	uint32_t sid = 0;
	if( argc == 2 ) sid = atoi(argv[1]);
	printf("SEED: %d\n",sid);
	rng.seed( sid );

	physics.Init( argc, argv, new ContactListener() );
	renderer.Prepare( gl, &cam, winWidth, winHeight );
	assets.Prepare( gl );
	//map = mapgen::Generar( rng, mapgen::RoomGenConfig(), room_list);

	mapgen::GenRooms( rng, mapdata.config, mapdata.rooms );
	printf("n: %zu\n", mapdata.rooms.Size() );
	map = mapgen::RasterMapData( mapdata );

	for(int i = 0; i < map.Width(); i++ )
	{
		for( int j = 0; j < map.Height(); j++ )
		{
			if( map.Get(i,j) != Map::BLOCK_FREE )
				physics.AddCubeBody(-i*2,-j*2);
		}
	}

	cam.SetPosition( cml::vector3f(0,0,0) );
	cam.SetHorizontalAngle( 90 );

	plane.Prepare(gl,300,300,4,4);
	efactory.Prepare( &physics, &assets, &entityList, &sceneRoot );

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



void App::PurgeList( DynamicArray<Entity*>& l )
{
	for( size_t i = 0; i < l.Size(); i++ )
	{
		if( !l[i]->IsAlive() )
		{
			l[i]->Cleanup();
			//if( l[i]->controller != NULL ) delete l[i]->controller;
			//l[i]->GetPhysicBody()->GetWorld()->DestroyBody(l[i]->GetPhysicBody());
			delete l[i];
			l[i] = l[l.Size()-1];
			l.RemoveLast(); // dealloc!! se olvida?
			i--;
		}
	}
}

void App::Update(uint32_t delta)
{

	SDL_WarpMouseInWindow( NULL, 400, 300 );

	// Update everything
	this->sceneRoot.Update(Transform(), delta);
	physics.Step();
	player->PhysicStep();
	player->Step( delta );
	if( !player->IsAlive() ) Stop();

	// Clean dead entities
	this->sceneRoot.UpdateClean();
	PurgeList(entityList);

	if( player->attack ) assets.Sprite(S3D_ARMA)->SetCurrentFrame(1,1);
	else assets.Sprite(S3D_ARMA)->SetCurrentFrame(0,1);

	deltatime = delta;
}

void App::Render()
{

	// SETUP CAMERA
	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
	cam.SetPosition(cml::vector3f(ppos.x, 0, ppos.y));
	cam.SetHorizontalAngle(-player->GetAngleY());

	renderer.SetupRender();

	cml::matrix44f_c model = cml::identity<4>();
	cml::matrix_rotation_world_x( model, cml::rad(90.f) );
	cml::matrix_set_translation( model, 0.f, 2.f, 0.f );
	renderer.RenderPlane( &plane, model, assets.Texture(TEX_SUELO) );

	model = cml::identity<4>();
	cml::matrix_rotation_world_x( model, cml::rad(-90.f) );
	cml::matrix_set_translation( model, 0.f, -2.f, 300.f );
	renderer.RenderPlane( &plane, model, assets.Texture(TEX_TECHO) );

	renderer.RenderMap( map, assets.Texture(TEX_TEX1), assets.Texture(TEX_TEX2), assets.Texture(TEX_TEX3) );
	renderer.BatchSprite3D();

	for( size_t i = 0; i < entityList.Size(); i++ )
	{
		entityList[i]->PhysicStep();
		entityList[i]->ClearVelocity();
		entityList[i]->SetAngleY( cml::rad(180 + player->GetAngleY()) );
		renderer.RenderEntity( entityList[i] );
	}

	gl->Disable(GL_DEPTH_TEST);
	RenderWeapon();

	RenderMiniText();
	RenderPlayerHP();

	renderer.RenderFinish( mainWindow, deltatime );

}

void App::RenderWeapon()
{
	cml::matrix44f_c model = cml::identity<4>();
	model = cml::identity<4>();
	cml::vector3f offset(0,0,0);
	offset = cml::rotate_vector( cml::vector3f(1,0,0), cml::vector3f(0,1,0), cml::rad(player->GetAngleY()+90) );
	cml::matrix_set_translation( model, player->GetTransform().position + offset );
	cml::matrix_rotate_about_world_y( model, cml::rad(180+player->GetAngleY()) );
	renderer.RenderSprite3D( assets.Sprite(S3D_ARMA), model );
}

void App::RenderMiniText()
{
	uint32_t time = SDL_GetTicks();
	float r = sin(((float)time)/10);
	float g = sin(((float)time)/40);
	float b = sin(((float)time)/400);
    renderer.RenderText("Miniray", -0.35, 0.7, cml::vector4f(b,g,r,1));
}

void App::RenderPlayerHP()
{
    char buf[8];
    sprintf(buf, "%d", player->hp.current);
	float phealth = float(player->hp.current) / float(player->hp.total);
    renderer.RenderText(buf, -1, -0.97, cml::vector4f(1-phealth,phealth,0,1));

    sprintf(buf, "%d", player->ammo);
    renderer.RenderText(buf, 0.5, -0.97, cml::vector4f(1,0.5,0,1));
}


void App::HandleEvent(SDL_Event& event)
{
	if( playercontroller->HandleEvent( event ) == 0 )
	{
		switch( event.type )
		{
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_ESCAPE ) Stop();
			else if( event.key.keysym.sym == SDLK_p ) renderer.UseDefaultFBO();
			else if( event.key.keysym.sym == SDLK_o ) renderer.UseCreatedFBO();
			break;
		}
	}
}

void App::Cleanup()
{
	plane.Dispose(gl);
	renderer.Dispose( );
	for( size_t i = 0; i < entityList.Size(); i++ )
	{
		//if( entityList[i]->controller ) delete entityList[i]->controller;
		delete entityList[i];
	}
	physics.Cleanup();
}
