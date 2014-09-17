
#pragma once

#include <cml/cml.h>

class Transform
{

public:

	cml::vector3f position;
	cml::vector3f rotation;

	Transform()
	{
		position = cml::vector3f(2,0,2);
		rotation = cml::vector3f(0,0,0);
	}

	cml::matrix44f_c Model()
	{
		cml::matrix44f_c model = cml::identity<4>();
		cml::matrix_rotation_euler( model, rotation[0], rotation[1], rotation[2], cml::EulerOrder::euler_order_yxz );
		cml::matrix_set_translation( model, position );
		return model;
	}

};
