
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

App::App() :
	SDLGLApp( 800, 600 )
{
}

void App::SetupPlayer()
{
	player = new Player();
	player->SetSprite(NULL);
	player->SetType(CollisionLayer::PLAYER);
	player->SetPhysicBody(physics.CreateSphereBody(-30, -30));
	this->playercontroller = new PlayerHumanController();
	player->SetController( this->playercontroller );
	//actors.Add( player );
}

void App::Setup(int argc, char** argv)
{
	//map.LoadFromFile( "mimapa.txt" );
	//map.Debug();

	SDL_ShowCursor(0);

	physics.Init( argc, argv );
	renderer.Prepare( gl );

	cam.SetPosition( cml::vector3f( -30, 0, -30 ) );
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
	map.Debug();

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

	bichosprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), persotex, 1, 1 );
	bichosprite.SetCurrentFrame( 0, 0 );

	bulletsprite.Prepare( gl, cml::vector3f( 6, 0, 4 ), bullettex, 1, 1 );
	bulletsprite.SetCurrentFrame( 0, 0 );

	for( int i = 0; i < 100; i++ )
	{
		Entity* ent = new Entity();
		ent->SetSprite( &bichosprite );
		//ent->GetTransform().position = cml::vector3f( i*2, 0, 30 );
		ent->SetPhysicBody( physics.CreateSphereBody( -i*2, -30 ) );
		actors.Add( ent );
	}

	SetupPlayer();
	//bichoentity.SetSprite( &bichosprite );

	timer = 0; coord = 0;
}


void App::SpawnBullet( cml::vector2f pos, cml::vector2f dir )
{
	Entity* ent = new Entity();
	ent->SetType( CollisionLayer::PLAYER_BULLET );
	b2Body* b = physics.CreateBulletBody( pos[0], pos[1] );
	b->SetLinearVelocity(b2Vec2( dir[0], dir[1] ));
	ent->SetPhysicBody(b);
	ent->SetSprite(&bulletsprite);
	bullets.Add(ent);
}

void App::PurgeList( DynamicArray<Entity*>& l )
{
	for( int i = 0; i < l.Size(); i++ )
	{
		if( !l[i]->IsAlive() )
		{
			l[i]->Cleanup();
			delete l[i];
			l[i] = l[l.Size()-1];
			l.RemoveLast();
			i--;
		}
	}
}

void App::Update(uint32_t delta)
{
	timer += delta;
	if( timer > 1000 )
	{
		coord = (((int)coord)+1)%2;
		timer = 0;
	}

	// step
	// ENTITIES STEP
	SDL_WarpMouseInWindow( NULL, 400, 300 );
	for( int i = 0; i < actors.Size(); i++ )
	{
		actors[i]->Step( delta );
	}

	player->Step( delta );
	cam.SetPosition(cml::vector3f(0,0,0));
	cam.SetHorizontalAngle(-player->GetAngleY());
	// PHYSICS STEP
	physics.Step();
	player->PhysicStep();

	PurgeList(actors);
	PurgeList(bullets);
	/*
	if( caminput.shoot )
	{
		printf("DISPARARRRR\n");
		cml::vector3f pos = player.GetTransform().position;
		cml::vector2f pos2d(pos[0],pos[2]);
		cml::vector2f finaldir = cml::rotate_vector_2D( cml::vector2f(0,1), cml::rad(cam.GetHorizontalAngle()) );
		printf("finaldir: %f, %f\n", finaldir[0], finaldir[1] );
		SpawnBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * 20);
	}
	*/

	int bicho = 5;
	//cam.SetHorizontalAngle( playerBody->GetAngle() );


	//bichosprite.SetAngleY( cam.GetHorizontalAngle() );
}

void App::Render()
{

	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
	cam.SetPosition(cml::vector3f(ppos.x, 0, ppos.y));

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
	//renderer.RenderSprite3D( bichosprite, bichoentity.Model() );
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

	//renderer.RenderEntity( bichoentity );
	renderer.RenderFinish( mainWindow );

}


void App::HandleEvent(SDL_Event& event)
{
	if( playercontroller->HandleEvent( event ) == 0 )
	{
		switch( event.type )
		{
		case SDL_KEYDOWN:
			if( event.key.keysym.sym == SDLK_ESCAPE ) Stop();
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
		delete actors[i];
	}
}
