
#include "app.h"
#include "../render/block.h"
#include "../texgen/canvas.h"
#include "../texgen/color.h"
#include "../texgen/texgen.h"
#include "../core/matrix2d.h"
#include "../map/mapgen.h"
#include "../entity/entity.h"
#include "../entity/player.h"
#include "../physics/layers.h"
#include "../entity/controller/playerhumancontroller.h"
#include "../entity/controller/entitycontroller.h"
#include "../entity/controller/mobaicontroller.h"
#include "../core/random.h"

App::App() :
	SDLGLApp( 800, 600 )
{
}

void App::SetupPlayer()
{
	player = new Player();
	player->SetSprite(NULL);
	player->SetType(Entity::Type::PLAYER);
	player->SetPhysicBody(physics.CreateSphereBody(-30, -30, CollisionLayer::PLAYER, Physics::PLAYER_MASK ));
	this->playercontroller = new PlayerHumanController();
	player->SetController( this->playercontroller );
	System::SetPlayerEntity( player );
	player->hp.current = 200;
	player->hp.total = 200;
		//actors.Add( player );
}

void App::Setup(int argc, char** argv)
{
	//map.LoadFromFile( "mimapa.txt" );
	//map.Debug();

	SDL_ShowCursor(0);

	physics.Init( argc, argv );
	renderer.Prepare( gl, winWidth, winHeight );

	cam.SetPosition( cml::vector3f( -0, 0, -0 ) );
	cam.SetHorizontalAngle( 90 );

	int w, h;
	w = h = 512;
	canvas = new Canvas( w,h );
	canvas->Fill( Color(0,0,0,255) );

	//canvas->GenClouds( rng );
	//canvas->GenTurbulence( rng, 64, 2048, false );
	canvas->GenPixelTurbulence( rng, 64, 32 );

	/*
	for( int i = 0; i < 32*32; i++ )
	{
		printf("%u ", ((unsigned char*)canvas->Raw())[i]);
	}
	*/

	Canvas cv(w,h);

	plane.Prepare(gl,300,300,4,4);
	mapgen::Config cfg;
	map = mapgen::Generar(cfg);
	for(int i = 0; i < map.Width(); i++ )
	{
		for( int j = 0; j < map.Height(); j++ )
		{
			if( map.Getint(i,j) != Map::BLOCK_FREE )
				physics.AddCubeBody(-i*2,-j*2);
		}
	}
	//map.Debug();

	rzfx::noise( cv );
	//rzfx::turbulence( cv );
	pbmp = new tdogl::Bitmap( w, h, tdogl::Bitmap::Format::Format_RGBA, ((unsigned char*)cv.Raw() ));

    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile("data/qwe.png");
    bmp.flipVertically();
    tex1 = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/asd.png");
	bmp.flipVertically();
	tex2 = new tdogl::Texture(gl, bmp);
	//tex2 = new tdogl::Texture(gl, *pbmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/asd2.png");
	bmp.flipVertically();
	tex3 = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/suelo.png");
	bmp.flipVertically();
	suelotex = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/techo.png");
	bmp.flipVertically();
	techotex = new tdogl::Texture(gl, bmp);

	/*
	bmp = tdogl::Bitmap::bitmapFromFile("data/cosarara_sheet.png");
	bmp.flipVertically();
	persotex = new tdogl::Texture(gl, bmp);

	bichosprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), persotex, 3, 4 );
	bichosprite.SetCurrentFrame( 2, 2 );
	*/

	bmp = tdogl::Bitmap::bitmapFromFile("data/rob.png");
	bmp.flipVertically();
	persotex = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/bullet.png");
	bmp.flipVertically();
	bullettex = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/redbullet.png");
	bmp.flipVertically();
	redtex = new tdogl::Texture(gl, bmp);

	bmp = tdogl::Bitmap::bitmapFromFile("data/arma.png");
	bmp.flipVertically();
	armatex = new tdogl::Texture(gl, bmp);

	bichosprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), persotex, 1, 1 );
	bichosprite.SetCurrentFrame( 0, 0 );

	bulletsprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), bullettex, 1, 1 );
	bulletsprite.SetCurrentFrame( 0, 0 );

	redsprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), redtex, 1, 1 );
	redsprite.SetCurrentFrame( 0, 0 );

	armasprite.Prepare( gl, cml::vector3f(0,0,0), armatex, 2, 2 );
	armasprite.SetCurrentFrame( 0, 0 );

	RNG rng;

	for( int i = 0; i < 300; i++ )
	{
		Entity* ent = new Actor();
		Actor* actor = static_cast<Actor*>(ent);
		actor->hp.current = 10;
		actor->wep.rate = 20;
		actor->wep.bullet_speed = 20;
		actor->wep.bullet_duration = 30;

		ent->controller = new MobAIController();
		ent->SetSprite( &bichosprite );
		//ent->GetTransform().position = cml::vector3f( i*2, 0, 30 );
		int xcoord = rng.uniform(0, map.Width()-1);
		int ycoord = rng.uniform(0, map.Height()-1);
		//printf("%d,%d\n", xcoord, ycoord);
		ent->SetPhysicBody( physics.CreateSphereBody( -xcoord*2, -ycoord*2 ) );
		//ent->SetPhysicBody( physics.CreateSphereBody( -i*2, -30 ) );
		actors.Add( ent );
	}

	SetupPlayer();
	//bichoentity.SetSprite( &bichosprite );

	timer = 0; coord = 0;

	efactory.SetLists(&actors, &bullets);
	efactory.SetPhysics( &physics );
	efactory.SetBulletSprite( &bulletsprite, &redsprite );
	EntityController::SetEntityFactory( &efactory );

}


void App::SpawnBullet( cml::vector2f pos, cml::vector2f dir )
{
	/*
	Entity* ent = new Entity();
	ent->SetType( CollisionLayer::PLAYER_BULLET );
	b2Body* b = physics.CreateBulletBody( pos[0], pos[1] );
	b->SetLinearVelocity(b2Vec2( dir[0], dir[1] ));
	ent->SetPhysicBody(b);
	ent->SetSprite(&bulletsprite);
	bullets.Add(ent);
	*/
}

void App::PurgeList( DynamicArray<Entity*>& l )
{
	for( int i = 0; i < l.Size(); i++ )
	{
		if( !l[i]->IsAlive() )
		{
			l[i]->Cleanup();
			if( l[i]->controller != NULL ) delete l[i]->controller;
			delete l[i];
			l[i] = l[l.Size()-1];
			l.RemoveLast(); // dealloc!! se olvida?
			i--;
		}
	}
}

void App::UpdateActors( uint32_t delta )
{
	for( int i = 0; i < actors.Size(); i++ )
	{
		actors[i]->Step( delta );
	}
	for( int i = 0; i < bullets.Size(); i++ )
	{
		bullets[i]->Step( delta );
	}
}

void App::Update(uint32_t delta)
{

	// step
	// ENTITIES STEP
	SDL_WarpMouseInWindow( NULL, 400, 300 );

	// PHYSICS QUERY AABB STRESS TEST
	//physics.Stress(this->player);

	UpdateActors(delta);

	physics.Step();
	player->PhysicStep();
	player->Step( delta );
	if( !player->IsAlive() ) Stop();

	PurgeList(actors);
	PurgeList(bullets);

	if( player->attack ) armasprite.SetCurrentFrame( 1, 1 );
	else armasprite.SetCurrentFrame( 0, 1 );

	deltatime = delta;
	int bicho = 5;
	//cam.SetHorizontalAngle( playerBody->GetAngle() );


	//bichosprite.SetAngleY( cam.GetHorizontalAngle() );
}

void App::Render()
{

	// SETUP CAMERA
	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
	cam.SetPosition(cml::vector3f(ppos.x, 0, ppos.y));
	cam.SetHorizontalAngle(-player->GetAngleY());

	// SETUP MVP MATRICES
	renderer.BindPostFBO();
	gl->Enable(GL_DEPTH_TEST);
	renderer.SetVP( cam.GetView(), cam.GetProjection() );
	renderer.RenderClear();

	cml::matrix44f_c model = cml::identity<4>();
	cml::matrix_rotation_world_x( model, cml::rad(90.f) );
	cml::matrix_set_translation( model, 0.f, 2.f, 0.f );
	renderer.RenderPlane( &plane, model, suelotex );

	model = cml::identity<4>();
	cml::matrix_rotation_world_x( model, cml::rad(-90.f) );
	cml::matrix_set_translation( model, 0.f, -2.f, 300.f );
	renderer.RenderPlane( &plane, model, techotex );

	renderer.RenderMap( map, tex1, tex2, tex3 );
	renderer.BatchSprite3D();
	for( int i = 0; i < actors.Size(); i++ )
	{
		actors[i]->SetAngleY( cml::rad(180 + player->GetAngleY() ) );
		actors[i]->PhysicStep();
		actors[i]->ClearVelocity();
		renderer.RenderEntity( actors[i] );
	}

	for( int i = 0; i < bullets.Size(); i++ )
	{
		bullets[i]->SetAngleY( cml::rad(180 + player->GetAngleY()) );
		bullets[i]->PhysicStep();
		renderer.RenderEntity( bullets[i] );
	}

	model = cml::identity<4>();
	cml::vector3f offset(0,0,0);
	offset = cml::rotate_vector( cml::vector3f(1,0,0), cml::vector3f(0,1,0), cml::rad(player->GetAngleY()+90) );
	cml::matrix_set_translation( model, player->GetTransform().position + offset );
	cml::matrix_rotate_about_world_y( model, cml::rad(180+player->GetAngleY()) );
	renderer.RenderSprite3D( armasprite, model );


	//gl->Enable(GL_BLEND);
    //gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	timer += deltatime;
	float r = sin(((float)timer)/10);
	float g = sin(((float)timer)/40);
	float b = sin(((float)timer)/400);
    renderer.RenderText("Miniray", -0.35, 0.7, cml::vector4f(b,g,r,1));
    char buf[8];
    sprintf(buf, "%d", player->hp.current);
	float phealth = float(player->hp.current) / float(player->hp.total);
    renderer.RenderText(buf, -1, -0.97, cml::vector4f(1-phealth,phealth,0,1));

    sprintf(buf, "%d", player->ammo);
    renderer.RenderText(buf, 0.5, -0.97, cml::vector4f(1,0.5,0,1));
    //renderer.RenderText("The Misaligned Fox Jumps Over The Lazy Dog", -1, -1);
	//renderer.RenderText("The Small Texture Scaled Fox Jumps Over The Lazy Dog", -0.5, -0.5, cml::vector4f(0,0,1,1), 0.5, 0.5);
	renderer.RenderFinish( mainWindow, deltatime );

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
	bichosprite.Dispose(gl);
	renderer.Dispose( );
	for( int i = 0; i < actors.Size(); i++ )
	{
		if( actors[i]->controller ) delete actors[i]->controller;
		delete actors[i];
	}
}
