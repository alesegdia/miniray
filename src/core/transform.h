
#pragma once

#include <cml/cml.h>
#include "../core/dynamicarray.h"

class Transform
{

public:

	DynamicArray<Transform*> children;
	cml::vector3f position;
	cml::vector3f rotation;
	cml::vector3f local_position;
	cml::vector3f local_rotation;
	cml::matrix44f_c world;

	Transform()
	{
		position = cml::vector3f(0,0,0);
		rotation = cml::vector3f(0,0,0);
	}
	
	void Update( Transform parent = Transform() )
	{
		world = cml::identity<4>();
		cml::matrix_rotation_euler( world, rotation[0], rotation[1], rotation[2], cml::EulerOrder::euler_order_yxz );
		cml::matrix_set_translation( world, position );
		
	}

	cml::matrix44f_c Model()
	{
		return world;
	}

};
