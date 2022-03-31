#pragma once

#include "Plane.h"
#include "ParticleSystem.h"
#include <iostream>
#include "Sphere_intermediate.h"
#include <math.h>
class Mathematics
{
public:
	Mathematics();
	Plane* GetPlane(glm::vec3 point,glm::vec3 normal);
	Plane* GetPlane(glm::vec3 point,glm::vec3 vec1, glm::vec3 vec2);
	void CheckCollisionWithPlane(Plane* plane, ParticleSystem* _ps);
	void Collide(Plane* plane,int index, ParticleSystem* _ps);
	Plane* GetPlaneFromPoints(glm::vec3 point1,glm::vec3 point2, glm::vec3 point3, ParticleSystem* _ps);
	bool HasCollidedWithSphere(Sphere_intermediate* sphere, glm::vec3 point);
	void GetSphereCollisionPlane(Sphere_intermediate* sphere, ParticleSystem* _ps);
	glm::vec3 Normalize(glm::vec3 vec);
	void CheckCollisionWithCapsule(glm::vec3 center1, glm::vec3 center2, float radius, ParticleSystem* _ps);
	void GetCapsuleCollisionPlane(int id, glm::vec3 center1, glm::vec3 center2, float radius, ParticleSystem* _ps);
private:
	//ParticleSystem* _ps;
};

