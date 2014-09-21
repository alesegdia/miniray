
#include "playerhumancontroller.h"
#include "../player.h"
#include "../entity.h"
#include "../script/playerweapon.h"
#include "../entityfactory.h"
#include "../system/system.h"
#include "../system/healthchecker.h"
#include <Box2D/Box2D.h>

PlayerHumanController::PlayerHumanController ()
{
	forward = back = left = right = false;

}

PlayerHumanController::~PlayerHumanController ()
{

}

void PlayerHumanController::Step( Entity* e, uint32_t delta )
{
	Player* p = static_cast<Player*>(e);
	p->attack = shoot;

	// MOVEMENT HANDLE
	rotation_offset[0] *= -sensitivity;
	p->OffsetRotationY( rotation_offset[0] );

	p->move_direction = axis;
	p->rotation_offset = rotation_offset;

	float speed = (shift?p->run_speed:p->walk_speed);

	{
		cml::vector2f finaldir(0,0);
		if( axis[0] != 0 || axis[1] != 0 )
		{
			axis.normalize();
			finaldir = cml::rotate_vector_2D( axis, -cml::rad(p->GetAngleY()));
		}
		p->GetPhysicBody()->SetLinearVelocity(b2Vec2(finaldir[0]*speed,finaldir[1]*speed));
	}
	printf("vida: %d\n", p->hp.current);
	CheckHealth( p );

	System::SetEntityFactory( EntityController::entityfactory );
	if( p->ammo > 0 && wpsys.TryShoot( e, static_cast<Weapon*>(&(p->weapon)), shoot, delta ) )
	{
		p->ammo--;
		// restar el bat y spr
	}

	/*
	PlayerWeapon* pw = p->weapon;
	if( shoot )
	{
		if( pw->last_shot >= pw->rate )
		{
			pw->Shoot();
			pw->last_shot = 0;
			p->BAT -= pw->BAT_per_shot;
			p->SPR -= pw->SPR_per_shot;
		}
		else
		{
			pw->last_shot += delta;
		}
	}
	else
	{
		pw->last_shot += delta;
	}
	*/
}

int PlayerHumanController::HandleEvent( SDL_Event& event )
{
	int ret = 0;
	switch( event.type ){
	case SDL_KEYDOWN:
		switch( event.key.keysym.sym )
		{
		case SDLK_w:
			forward = true;
			ret = 1;break;
		case SDLK_s:
			back = true;
			ret = 1;break;
		case SDLK_a:
			left = true;
			ret = 1;break;
		case SDLK_d:
			right = true;
			ret = 1;break;
		case SDLK_LSHIFT:
			shift = true;
			ret = 1;break;
		}
		break;
	case SDL_KEYUP:
		switch( event.key.keysym.sym )
		{
		case SDLK_w:
			forward = false;
			ret = 1;break;
		case SDLK_s:
			back = false;
			ret = 1;break;
		case SDLK_a:
			left = false;
			ret = 1;break;
		case SDLK_d:
			right = false;
			ret = 1;break;
		case SDLK_LSHIFT:
			shift = false;
			ret = 1;break;
		}
		break;
	case SDL_MOUSEMOTION:
		rotation_offset[0] = ((float)event.motion.x) - 400.f;
		rotation_offset[1] = ((float)event.motion.y) - 300.f;
		ret = 1;break;
	case SDL_MOUSEBUTTONUP:
		switch( event.button.button )
		{
		case SDL_BUTTON_LEFT:
			shoot = false;
			ret = 1;break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch( event.button.button )
		{
		case SDL_BUTTON_LEFT:
			shoot = true;
			ret = 1;break;
		}
		break;
	}

	axis[1] = (forward?1.f:(back?-1.f:0.f));
	axis[0] = (left?1.f:(right?-1.f:0.f));
	return ret;
}
