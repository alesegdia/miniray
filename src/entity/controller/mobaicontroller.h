
#pragma once

#include "entitycontroller.h"
#include "../system/healthchecker.h"
#include "../system/weaponsystem.h"
#include "../actor.h"
#include "../entity.h"
// mierda, el player deberia estar en el controller, pero bueno
#include "../system/system.h"
#include "../../core/random.h"


class MobAIController : public EntityController
{

	WeaponSystem wpsys;
	static RNG rng; // hacerlo puntero y pasarselo desde el main

	enum State {
		IDLE,
		HUNTING_PLAYER
	};

	class MyRayCB : public b2RayCastCallback
	{
		public:
			bool didcollide;

		void SetOrigin( b2Vec2 origin )
		{
			didcollide = false;
		}

		float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction )
		{
			if( fixture->GetFilterData().categoryBits == CollisionLayer::MAP )
			{
				didcollide = true;
				return 0;
			}
			return fraction;
		}
	};

	State st = State::IDLE;

public:


	void Step( Entity* e, uint32_t delta )
	{
		Actor* actor = static_cast<Actor*>(e);
		CheckHealth( actor );
		cml::vector3f mob2player = actor->transform.position - System::player->transform.position;
		float dist = cml::length( mob2player );
		if( !e->IsAlive() )
		{
			if( rng.uniform() > 0.6 )
			{
				printf("SUERTO!\n");
				printf("%f, %f\n", actor->transform.position[0], actor->transform.position[2]);
				entityfactory->SpawnPickup(cml::vector2f( -actor->transform.position[0], -actor->transform.position[2]));
			}
		}

		//actor->logic_angle += 0.01;
		//
		//actor->logic_angle = cml::rad(180.f+45.f);
		//printf("logic_angle: %f\n", actor->logic_angle);

		if( dist <  20.f  )
		{
			cml::vector2f mobv = cml::rotate_vector_2D( cml::vector2f(1,0), actor->logic_angle );
			cml::vector3f dif = actor->transform.position - System::player->transform.position;
			float ang = cml::deg(cml::signed_angle_2D( mobv, cml::vector2f(dif[0],dif[2]) ));
			if( abs(ang) < 90 )
			{
				b2Body* b = actor->GetPhysicBody();
				cml::vector3f actorpos = actor->transform.position;
				cml::vector3f playerpos = System::player->transform.position;
				if( actorpos != playerpos )
				{
					MyRayCB tehcb;
					tehcb.SetOrigin(b2Vec2(actorpos[0],actorpos[2]));
					b2Vec2 apos(-actorpos[0],-actorpos[2]);
					b2Vec2 ppos(-playerpos[0],-playerpos[2]);
					b->GetWorld()->RayCast( &tehcb, apos, ppos );
					if( tehcb.didcollide )
					{
						//printf("COLMAPA!!");
					}
					else
					{
						bool shoot = dist < 21.f;
						//wpsys.TryShoot( e, &(actor->wep), shoot, delta, System::player->transform.position );
						// SHOOT AT LOGIC_ANGLE DIRECTION!!
						//printf("GOGOGO\n");
						float degs = cml::deg(cml::signed_angle_2D(cml::vector2f(1,0), cml::vector2f(dif[0],dif[2])));
						//printf("logic: %f, ang: %f, degs: %f\n",cml::deg(actor->logic_angle),ang,degs);
						//while(degs>=360) degs -= 360;
						actor->logic_angle += cml::rad(ang);
						//actor->logic_angle = cml::rad(degs); //,difcml::deg(System::player->GetAngleY());
						cml::vector3f dirshoot = cml::rotate_vector( cml::vector3f(1,0,0), cml::vector3f(0,-1,0), cml::rad(180.f)+actor->logic_angle );
						wpsys.TryShoot( e, &(actor->wep), shoot, delta, actor->transform.position + dirshoot );

						if( mob2player != cml::zero<3>() ) mob2player.normalize();
						mob2player *= 4;
						actor->GetPhysicBody()->SetLinearVelocity(b2Vec2( mob2player[0], mob2player[2] ));
						//printf("LLEGA AL PLAYER!");
					}
				}

			}
		}
		/*
		b2RayCastInput rayinput;
		rayinput.p1 = actor->transform.position;
		rayinput.p2 = System::player->transform.position;
		rayinput.maxFraction = 2;

		bool playerInSight = false;
		for( b2Fixture* f = System::player->GetPhysicBody()->GetFixtureList(); f; f = f->GetNext() )
		{
			b2RayCastOutput rayoutput;
			if( f->RayCast( &rayoutput, rayinput ) )
			{

				break;
			}

		}
		*/
	}

};

