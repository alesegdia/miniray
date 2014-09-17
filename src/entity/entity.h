#pragma once

#include "../render/sprite3d.h"
#include "../core/transform.h"
#include "../physics/layers.h"

#include <Box2D/Box2D.h>

class EntityController;

class Entity
{

protected:

	Transform transform;
	Sprite3D* sprite;
	b2Body* body;

	bool isAlive;
	CollisionLayer type;
	EntityController* controller;


public:

	Entity()
	{
		isAlive = true;
		controller = NULL;
		type = CollisionLayer::ENEMY;
	}

	void ClearVelocity()
	{
		body->SetLinearVelocity(b2Vec2(0,0));
	}

	void SetController( EntityController* controller );

	void Step( uint32_t delta );

	void SetType( CollisionLayer t )
	{
		type = t;
	}

	CollisionLayer GetType()
	{
		return type;
	}

	void CollisionEnter( Entity* other )
	{
		printf("%p: START COLLISION WITH %p\n", this, other);
		fflush(0);
	}

	void CollisionExit( Entity* other )
	{
		printf("%p: END COLLISION WITH %p\n", this, other);
		fflush(0);
	}

	void Cleanup()
	{
		body->GetWorld()->DestroyBody( body );
	}

	void Die()
	{
		isAlive = false;
	}

	bool IsAlive()
	{
		return isAlive;
	}

	void SetPhysicBody( b2Body* body )
	{
		this->body = body;
		this->body->SetUserData(this);
	}

	b2Body* GetPhysicBody()
	{
		return body;
	}

	void SetSprite( Sprite3D* sprite )
	{
		this->sprite = sprite;
	}

	cml::matrix44f_c Model()
	{
		return transform.Model();
	}

	void SetAngleY( float angle )
	{
		transform.rotation[0] = angle;
	}

	float GetAngleY()
	{
		return transform.rotation[0];
	}

	void OffsetRotationY( float delta_angle )
	{
		transform.rotation[0] += delta_angle;
	}

	void Prepare( Sprite3D* sprite )
	{
		this->sprite = sprite;
	}

	Transform& GetTransform()
	{
		return transform;
	}

	void PhysicStep()
	{
		transform.position[0] = -this->body->GetPosition().x;
		transform.position[2] = -this->body->GetPosition().y;
	}

	Sprite3D* GetSprite()
	{
		return sprite;
	}

};
