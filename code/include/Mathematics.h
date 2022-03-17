#pragma once

#include "Plane.h"
#include "ParticleSystem.h"
#include <iostream>
#include "Sphere_intermediate.h"
#include <math.h>
class Mathematics
{
public:
	Mathematics(ParticleSystem* ps);
	Plane* GetPlane(glm::vec3 point,glm::vec3 normal);
	Plane* GetPlane(glm::vec3 point,glm::vec3 vec1, glm::vec3 vec2);
	void CheckCollisionWithPlane(Plane* plane);
	void Collide(Plane* plane,int index);
	Plane* GetPlaneFromPoints(glm::vec3 point1,glm::vec3 point2, glm::vec3 point3);
	bool HasCollidedWithSphere(Sphere_intermediate* sphere, glm::vec3 point);
	void GetSphereCollisionPlane(Sphere_intermediate* sphere);
	glm::vec3 Normalize(glm::vec3 vec);
private:
	ParticleSystem* _ps;
};

