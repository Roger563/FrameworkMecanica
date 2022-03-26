#pragma once
#include "ParticleSystem.h"
#include <glm\glm.hpp>
#include <time.h>
class CascadeEmitter
{
private:
	int _maxParticles;
	int _particleIndex;
	int _nextParticleToSpawn;
	int _firstActiveParticle;
	int _activeParticleCount;
	float _lifeTime;
	float _emissionRate;
	float _timeSinceLastemission;
	glm::vec3 _point1;
	glm::vec3 _point2;
	glm::vec3 _vect;
	glm::vec3 _spawningPos;
	glm::vec3 _acceleration;
	glm::vec3 _initialVelocity;
	float _lambda;
public:
	ParticleSystem* _particleSystem;
	CascadeEmitter(float lifeTime, float emissionRate, float elasticity);
	void SpawnParticle();
	void DespawnParticle(int index);
	void Update(float dt);

};

