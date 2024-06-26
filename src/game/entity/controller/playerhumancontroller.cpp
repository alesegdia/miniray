
#include "playerhumancontroller.h"
#include "../player.h"
#include <glrayfw/entity/entity.h>
#include "../script/playerweapon.h"
#include "../script/helpers.h"
#include "../entityfactory.h"
#include <Box2D/Box2D.h>

PlayerHumanController::PlayerHumanController (EntityFactory* efactory, Player* player)
{
	this->entityfactory = efactory;
	forward = back = left = right = shoot = shift = false;
	m_player = player;
	rotation_offset = { 0,0 };
}

PlayerHumanController::~PlayerHumanController ()
{

}

void PlayerHumanController::Step( Entity* e, uint32_t delta )
{
	Player* p = static_cast<Player*>(e);
	p->transform.logic_angle = -cml::rad(e->GetAngleY());
	p->attack = shoot;

	m_dashPower = p->slowdownTimer >= 0 ? m_dashPowerSlowdown : m_dashPowerBase;

	if (m_dashPressed && forward)
	{
		m_currentDashSpeed += p->GetForward() * m_dashPower;
	}
	if (m_dashPressed && back)
	{
		m_currentDashSpeed += cml::rotate_vector_2D(p->GetForward(), M_PI) * m_dashPower;
	}
	if (m_dashPressed && left)
	{
		m_currentDashSpeed += cml::rotate_vector_2D(p->GetForward(), M_PI + M_PI / 2) * m_dashPower;
	}
	if (m_dashPressed && right)
	{
		m_currentDashSpeed += cml::rotate_vector_2D(p->GetForward(), M_PI - M_PI / 2 ) * m_dashPower;
	}
	m_dashPressed = false;

	rotation_offset[0] *= -sensitivity;
	p->OffsetRotationY( rotation_offset[0] );

	p->move_direction = axis;
	m_currentDashSpeed *= m_dashDecay;
	p->rotation_offset = rotation_offset;

	float speed = (shift?p->stats.runSpeed:p->stats.walkSpeed);

	{
		cml::vector2f finaldir(0,0);
		if( axis[0] != 0 || axis[1] != 0 )
		{
			axis.normalize();
			finaldir = cml::rotate_vector_2D( axis, -cml::rad(p->GetAngleY()));
		}

		DoMove( p, cml::vector3f(finaldir[0] , 0, finaldir[1]), speed, m_currentDashSpeed);
		//p->GetPhysicBody()->SetLinearVelocity(b2Vec2(finaldir[0]*speed,finaldir[1]*speed));
	}
	CheckHealth( p );

    p->skillSet.SetPressed(shoot);
    p->skillSet.update(delta);

	p->pushback *= 0.8;

	if (p->absorbedDamageLastFrame)
	{
		p->slowdownTimer = p->stats.slowdownTimeOnParry;
	}

	if (p->slowdownTimer >= 0)
	{
		p->slowdownTimer -= delta;
	}

	p->absorbedDamageLastFrame = false;

	if (parryingRequested)
	{
		if (p->parryTimer <= 0 && p->parryCooldownTimer <= 0)
		{
			p->parryTimer = p->stats.parryingTime;
			p->parryCooldownTimer = p->stats.parryCooldown;
		}
	}
	parryingRequested = false;

	if (p->parryCooldownTimer >= 0)
	{
		p->parryCooldownTimer -= delta;
	}

	if (p->parryCooldownTimer >= 0)
	{
		p->parryCooldownTimer -= delta;
	}

	if (p->parryTimer >= 0)
	{
		p->parryTimer -= delta;
	}

	p->invincible = p->parryTimer >= 0;

	/*
    if( p->ammo > 0 && DoShoot( static_cast<Weapon*>(&(p->weapon)), shoot, delta ) )
	{
		cml::vector2f shootdir = GetForward( p ); //Rotate2D( cml::vector2f(0.f,1.f), cml::rad(-e->GetAngleY()) );
        entityfactory->SpawnPlayerBullet(
                    GetWorld2DPos( e->transform.position ) + shootdir * 4,
                    shootdir * p->weapon.bullet_speed,
                    p->weapon.bullet_duration
        );
        p->ammo--;
		// restar el bat y spr
	}
	*/

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
	int keysym = -1;
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
		case SDLK_SPACE:
			m_dashPressed = true;
			ret = 1; break;
		}
		keysym = event.key.keysym.sym;
		if (keysym >= SDLK_1 && keysym <= SDLK_4)
		{
			int slotidx = keysym - SDLK_0;
			m_player->skillSet.SetCurrentSlot(slotidx);
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
		case SDLK_SPACE:
			m_dashPressed = false;
			ret = 1; break;
		}
		break;
	case SDL_MOUSEMOTION:
		rotation_offset[0] = event.motion.x - 400;
		rotation_offset[1] = event.motion.y - 300;
		lastMousePos.set(event.motion.x, event.motion.y);
		//std::cout << "mouse: " << rotation_offset[0] << ", " << rotation_offset[1] << std::endl;
		SDL_WarpMouseInWindow(NULL, 400, 300);
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
		case SDL_BUTTON_RIGHT:
			parryingRequested = true;
			ret = 1;break;
		}
		break;
	}

	axis[1] = (forward?1.f:(back?-1.f:0.f));
	axis[0] = (left?1.f:(right?-1.f:0.f));
	return ret;
}
