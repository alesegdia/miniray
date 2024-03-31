#include "game/app/gamescreen.h"

#include "game/entity/entityfactory.h"
#include "game/entity/controller/playerhumancontroller.h"
#include "game/entity/controller/mobaicontroller.h"
#include "game/entity/player.h"
#include "game/physics/contactlistener.h"
#include "game/render/assets.h"
#include "mainscreen.h"

#include "game/app/persistentdata.h"

void GameScreen::SetupPlayer()
{
	cml::vector2i playerpos = mapdata.rooms[0].RandomPosition(rng, 3);
	player = this->efactory->SpawnPlayer(playerpos[0], playerpos[1]);
	this->playercontroller = static_cast<PlayerHumanController*>(player->controller);
	//efactory->SpawnPortal(playerpos[0] + 2, playerpos[1] + 2);
}

void GameScreen::Setup(const std::vector<std::string>& args)
{
	engine()->Reset(new ContactListener());
	uint32_t sid = 0;
	if (args.size() == 2) sid = atoi(args[1].c_str());
	printf("SEED: %d\n", sid);
	rng.seed(time(NULL));

	mapgen::RoomGenConfig cfg;
	cfg.num_rooms = PlayerPersistentData::GetInstance().GetRunPersistentData().GetCurrentFloor() + 2;

	mapdata = mapgen::GenRooms(rng, cfg);

	int a = 3;

	Matrix2D tilemap = mapgen::RasterMapData(mapdata);

	engine()->LoadScene(tilemap);
	engine()->SetSceneTextures({
			Assets::GetInstance().Texture("TEX_TEX1"),
			Assets::GetInstance().Texture("TEX_TEX2"),
			Assets::GetInstance().Texture("TEX_TEX3")
		},
		Assets::GetInstance().Texture("TEX_SUELO"),
		Assets::GetInstance().Texture("TEX_TECHO")
	);

	efactory = std::make_shared<EntityFactory>(engine()->GetPhysics(), engine()->emanager(), engine()->sceneRoot());

	for (size_t i = 1; i < mapdata.rooms.Size(); i++)
	{
		int lim = rng.uniform(6, 11);
		auto spawnerPos = mapdata.rooms[i].RandomPosition(rng, 1);
		efactory->SpawnSpawner(mapdata.rooms[i].x, mapdata.rooms[i].y);
		/*
		for (int j = 0; j < lim; j++)
		{
			cml::vector2i enemypos = mapdata.rooms[i].RandomPosition(rng, 1);
			efactory->SpawnEnemy(enemypos[0], enemypos[1]);
		}
		*/
	}

	cml::vector2i portalpos = mapdata.rooms[mapdata.rooms.Size() - 1].RandomPosition(rng, 1);
	efactory->SpawnPortal(portalpos[0], portalpos[1]);


	SetupPlayer();

	MobAIController::Prepare(this->player, efactory.get());

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
	player->Step(delta);
	if (!player->IsAlive())
	{
		SetNextScreen(std::make_shared<MainScreen>());
	}

	if (player->parryTimer >= 0)
	{
		Assets::GetInstance().Sprite("S3D_ARMA")->SetCurrentFrame(1, 0);
	}
	else
	{
		if (player->attack) Assets::GetInstance().Sprite("S3D_ARMA")->SetCurrentFrame(1, 1);
		else Assets::GetInstance().Sprite("S3D_ARMA")->SetCurrentFrame(0, 1);
	}

	engine()->renderer()->Update();

	if (player->touchPortal)
	{
		player->touchPortal = false;
		SetNextScreen(std::make_shared<NextFloorScreen>());
	}
}

void GameScreen::Render()
{

	if (player->painLastFrame)
	{
		player->painLastFrame = false;
		engine()->renderer()->AddShake(0.00015f);
		engine()->renderer()->AddRedScreen(0.5f);
	}

	if (player->hpLastFrame)
	{
		player->hpLastFrame = false;
		engine()->renderer()->AddGreenScreen(1.0f);
	}

	if (player->ammoLastFrame)
	{
		player->ammoLastFrame = false;
		engine()->renderer()->AddOrangeScreen(0.5f);
	}

	engine()->renderer()->AddShake(player->skillSet.GetCurrentSkill()->ConsumeShakeLastFrame());

	// SETUP CAMERA
	b2Vec2 ppos = player->GetPhysicBody()->GetPosition();
	engine()->cam()->position(cml::vector3f(ppos.x, 0, ppos.y));
	engine()->cam()->horizontalAngle(-player->GetAngleY());

	engine()->sceneRender(player->GetAngleY());

	RenderWeapon(cml::vector3f(0, 0, 0));
	RenderMiniText();
	RenderPlayerHP();

	engine()->renderer()->SetPlayerHealth(float(player->hp.current) / 30.f);
}

void GameScreen::RenderWeapon(cml::vector3f walkOffset)
{
	engine()->gl()->Disable(GL_DEPTH_TEST);
	cml::matrix44f_c model = cml::identity<4>();
	model = cml::identity<4>();
	cml::vector3f offset(0, 0, 0);
	offset = cml::rotate_vector(cml::vector3f(0.65, 0, 0), cml::vector3f(0, 1, 0), cml::rad(player->GetAngleY() + 90));
	cml::matrix_set_translation(model, player->GetTransform().position + offset + walkOffset);
	cml::matrix_rotate_about_world_y(model, cml::rad(180 + player->GetAngleY()));
	engine()->renderer()->RenderSprite3D(Assets::GetInstance().Sprite("S3D_ARMA"), model);
}

void GameScreen::RenderMiniText()
{
	uint32_t time = SDL_GetTicks();
	float r = sinf((float(time)) / 10);
	float g = sinf((float(time)) / 40);
	float b = sinf((float(time)) / 400);
	engine()->renderer()->renderText("Miniray", -0.35f, 0.7f, cml::vector4f(b, g, r, 1));
}

void GameScreen::RenderPlayerHP()
{
	char buf[8];
	sprintf(buf, "%d", player->hp.current);
	float phealth = float(player->hp.current) / float(player->hp.total);
	engine()->renderer()->renderText(buf, -1, -0.97f, cml::vector4f(1 - phealth, phealth, 0, 1));

	sprintf(buf, "%d", player->skillSet.GetAmmo());
	engine()->renderer()->renderText(buf, 0.7, -0.97f, cml::vector4f(1, 0.5, 0, 1));

	sprintf(buf, "%d", player->skillSet.GetCurrentSlot());
	engine()->renderer()->renderText(buf, -0.04f, -0.97f, cml::vector4f(1, 1, 1, 1));

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
	engine()->renderer()->renderText(arma.c_str(), 0.2f, -0.97f, cml::vector4f(1, 1, 1, 1));
}


void GameScreen::HandleEvent(SDL_Event& event)
{
	if (playercontroller->HandleEvent(event) == 0)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_p) engine()->renderer()->useDefaultFBO();
			else if (event.key.keysym.sym == SDLK_o) engine()->renderer()->useCreatedFBO();
			else if (event.key.keysym.sym == SDLK_r) RequestExit();
			break;
		}
	}
}

void GameScreen::Cleanup()
{

}
