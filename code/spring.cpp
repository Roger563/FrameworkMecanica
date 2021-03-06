#include "spring.h"

spring::spring(int particle1Index, int particle2Index, float restingLength, ParticleSystem* particleSystem, float k,float damping)
{
	_particle1Index = particle1Index;
	_particle2Index = particle2Index;
	_restLength = restingLength;
	_k = k;
	_particleSystem = particleSystem;
	_damping = damping;
}     



void spring::UpdateSpring()
{
	glm::vec3 springVector =  _particleSystem->GetParticlePosition(_particle1Index)- _particleSystem->GetParticlePosition(_particle2Index);
	float currentLenght = glm::length(springVector);
	//we normalize the vector
	glm::normalize(springVector);
	float stretch = currentLenght - _restLength;
	//_force =springVector * (-_k * stretch);
	_force =-( (_k * stretch) + glm::dot((_damping * (_particleSystem->GetParticleVelocity(_particle1Index) - _particleSystem->GetParticleVelocity(_particle2Index)) ), springVector) ) * springVector;
	//ApplyForces
	_particleSystem->ApplyForce(_particle1Index,  _force);
	_particleSystem->ApplyForce(_particle2Index,  -_force);
}


