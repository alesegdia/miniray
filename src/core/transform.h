
#pragma once

#include <cml/cml.h>
#include "../core/dynamicarray.h"

class Entity;

class Transform
{

public:

	float logic_angle = 0.f;
	DynamicArray<Transform*> children;
	cml::vector3f position;
	cml::vector3f rotation;
	cml::vector3f local_position;
	cml::vector3f local_rotation;
	cml::matrix44f_c world;
	cml::matrix44f_c local;
	Entity* entity;
	

	Transform();
	
	void Update( const Transform& parent );
	
	void Update2( const Transform& parent );

	void AddChild( Transform* child );

	cml::matrix44f_c Model();

};
