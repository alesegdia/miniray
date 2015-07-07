#pragma once

#include <cml/cml.h>

class Camera {
public:


	Camera();

	void SetAspect( float a );
	void SetPosition( const cml::vector3f& pos );
	void OffsetPosition( const cml::vector3f& offsetPosition );
	const cml::vector3f& GetPosition() const;
	void OffsetAngle( float hor, float ver );
	cml::matrix44f_c Matrix();
	float GetHorizontalAngle() const;
	float GetVerticalAngle() const;
	void SetHorizontalAngle( float angle )
	{
		horizontalAngle = angle;
	}
	const cml::matrix44f_c& GetProjection();
	const cml::matrix44f_c& GetView();

	cml::vector3f Forward() const;
	cml::vector3f Right() const;
	cml::vector3f Up() const;


private:

	void ComputeProjection();
	void ComputeView();

	// Perspective controls
	float fieldOfView;		// Field of View Angle
	float aspect;	// aspect Ratio
	float nearClip;	// Near clipping plane distance
	float farClip;	// Far clipping plane distance
	cml::matrix44f_c view, projection;

	// Transform
	cml::vector3f position;
	float horizontalAngle;
	float verticalAngle;

};

