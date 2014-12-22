
#include "transform.h"
#include "../entity/entity.h"

void Transform::Update(const Transform& parent, uint32_t delta)
{
	cml::matrix44f_c worldtrans,
					 localrot,
					 localtrans,
					 worldrot;

	worldtrans = localrot = localtrans = worldrot = worldtrans = cml::identity<4>();

	cml::vector3f loc = local_position;

	cml::matrix_rotation_euler( localrot, local_rotation[0], 0.f, 0.f, cml::EulerOrder::euler_order_yxz );
	cml::matrix_rotation_euler( worldrot, rotation[0], 0.f, 0.f, cml::EulerOrder::euler_order_yxz );
	// cml::matrix_rotation_euler( worldrot2, -rotation[0], 0.f, 0.f, cml::EulerOrder::euler_order_yxz );

	cml::matrix_set_translation( localtrans, local_position );
	cml::matrix_set_translation( worldtrans, position );

	world = parent.world * worldtrans * localrot * localtrans * worldrot;
	if( this->entity )
		this->entity->Step( delta );

	for( size_t i = 0; i < this->children.Size(); i++ )
	{
		// peta porque estamos actualizando un hijo que se ha eliminado (una bala probablemente, hija del nodo raiz)
		printf("%d\n", i);
		fflush(0);
		children[i]->Update(*this, delta);
	}
}

Transform::Transform()
{
	world = local = cml::identity<4>();
	position = rotation = local_position = local_rotation = cml::vector3f(0,0,0);
	this->entity = NULL;
}

void Transform::Update2(const Transform& parent)
{
	printf("HERE");
	// update local
	local = cml::identity<4>();
	cml::matrix_rotation_euler( local, local_rotation[0], local_rotation[1], local_rotation[2], cml::EulerOrder::euler_order_yxz );
	cml::matrix_set_translation( local, local_position );

	// update world
	cml::matrix44f_c tmp = cml::identity<4>();
	cml::matrix44f_c tmp2 = cml::identity<4>();
	cml::matrix_rotation_euler( tmp, 0.f, rotation[1], rotation[2], cml::EulerOrder::euler_order_yxz );
	cml::matrix_rotation_euler( tmp2, logic_angle, 0.f, 0.f, cml::EulerOrder::euler_order_yxz );

	cml::matrix_set_translation( tmp, position );
	world = parent.world * local * tmp2 * tmp;

	for( size_t i = 0; i < this->children.Size(); i++ ) {
		children[i]->Update2(*this);
	}
}

void Transform::AddChild(Transform* child)
{
	this->children.Add(child);
}

cml::matrix44f_c Transform::Model()
{
	return world;
}
