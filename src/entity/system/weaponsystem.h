
#pragma once

#include "system.h"
#include "../script/weapon.h"
#include "../entityfactory.h"
#include "../entity.h"

class WeaponSystem : public System {
public:

	bool TryShoot( Entity* shooter, Weapon* wp, bool shoot_key_pressed, uint32_t delta, const cml::vector3f& objective )
	{
		if( shoot_key_pressed )
		{
			if( wp->last_shot >= wp->rate )
			{
				cml::vector3f pos = shooter->GetTransform().position;
				cml::vector2f pos2d(pos[0],pos[2]);
				//cml::vector2f finaldir = cml::rotate_vector_2D( cml::vector2f(0,1), cml::rad(-shooter->GetAngleY()) );
				cml::vector3f finaldir3 = (shooter->transform.position-objective);
				//printf("vec3 %f, %f, %f\n", finaldir3[0], finaldir3[1], finaldir3[2]);
				cml::vector2f finaldir = cml::vector2f( finaldir3[0], finaldir3[2] );
				if( finaldir != cml::vector2f(0,0) ) finaldir.normalize();
				//printf("finaldir: %f, %f\n", finaldir[0], finaldir[1] );
				
				if( shooter->GetType() == Entity::Type::MOB )
				{
					System::entityfactory->SpawnEnemyBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed, wp->bullet_duration );
				}
				else
				{
					System::entityfactory->SpawnPlayerBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed, wp->bullet_duration );
				}
					//System::entityfactory->SpawnEnemyBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed);

				wp->last_shot = 0;
				//p->BAT -= pw->BAT_per_shot;
				//p->SPR -= pw->SPR_per_shot;
			}
			else
			{
				wp->last_shot += delta;
			}
		}
		else
		{
			wp->last_shot += delta;
		}
		return false;

	}

	bool TryShoot( Entity* shooter, Weapon* wp, bool shoot_key_pressed, uint32_t delta )
	{
		if( shoot_key_pressed )
		{
			if( wp->last_shot >= wp->rate )
			{
				cml::vector3f pos = shooter->GetTransform().position;
				cml::vector2f pos2d(pos[0],pos[2]);
				cml::vector2f finaldir = cml::rotate_vector_2D( cml::vector2f(0.f,1.f), cml::rad(-shooter->GetAngleY()) );
				//printf("finaldir: %f, %f\n", finaldir[0], finaldir[1] );
				if( shooter->GetType() == Entity::Type::MOB )
				{
					System::entityfactory->SpawnEnemyBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed, wp->bullet_duration);
				}
				else
				{
					System::entityfactory->SpawnPlayerBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed, wp->bullet_duration);
				}
				//System::entityfactory->SpawnEnemyBullet(cml::vector2f(-pos2d[0],-pos2d[1]) + finaldir, cml::vector2f(finaldir[0],finaldir[1]) * wp->bullet_speed);

				wp->last_shot = 0;
				//p->BAT -= pw->BAT_per_shot;
				//p->SPR -= pw->SPR_per_shot;
				return true;
			}
			else
			{
				wp->last_shot += delta;
			}
		}
		else
		{
			wp->last_shot += delta;
		}
		return false;
	}


private:
	/* data */
};

