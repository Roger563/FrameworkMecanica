#pragma once
#include <glm\glm.hpp>
#include "ParticleSystem.h"
class EulerIntegrator
{
public:
	EulerIntegrator(ParticleSystem* ps);
	void Step(float dt);
private:
	glm::vec3 CalculatePosition(int index,float dt);
	glm::vec3 CalculateVelocity(int index,float dt);
	ParticleSystem* _ps;
};

