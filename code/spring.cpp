#include "spring.h"

spring::spring(int particle1Index, int particle2Index, float restingLength, ParticleSystem* particleSystem, float k)
{
	_particle1Index = particle1Index;
	_particle2Index = particle2Index;
	_restLength = restingLength;
	_k = k;
	_particleSystem = particleSystem;
}



void spring::UpdateSpring()
{
	glm::vec3 springVector =  _particleSystem->GetParticlePosition(_particle2Index)- _particleSystem->GetParticlePosition(_particle1Index);
	float currentLenght = glm::length(springVector);
	glm::normalize(springVector);
	float stretch = currentLenght - _restLength;
	_force =springVector * (-_k * stretch);
	//ApplyForces
	_particleSystem->ApplyForce(_particle1Index,  -_force);
	_particleSystem->ApplyForce(_particle2Index,  _force);
}


