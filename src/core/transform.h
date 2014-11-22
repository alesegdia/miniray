
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
	cml::matrix44f_c local;
	

	Transform()
	{
		world = local = cml::identity<4>();
		position = rotation = local_position = local_rotation = cml::vector3f(0,0,0);
	}
	
	void Update( const Transform& parent )
	{
		// update local
		local = cml::identity<4>();
		cml::matrix_rotation_euler( local, local_rotation[0], local_rotation[1], local_rotation[2], cml::EulerOrder::euler_order_yxz );
		cml::matrix_set_translation( local, local_position );

		// update world
		cml::matrix44f_c tmp = cml::identity<4>();
		cml::matrix_rotation_euler( tmp, rotation[0], rotation[1], rotation[2], cml::EulerOrder::euler_order_yxz );
		cml::matrix_set_translation( tmp, position );
		world = local * tmp;

		for( int i = 0; i < this->children.Size(); i++ )
		{
			children[i]->Update(*this);
		}
	}
	
	void AddChild( Transform* child )
	{
		this->children.Add(child);
	}

	cml::matrix44f_c Model()
	{
		return world;
	}

};
