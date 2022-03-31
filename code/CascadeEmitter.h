#pragma once
#include "ParticleSystem.h"
#include <glm\glm.hpp>
#include <time.h>

namespace cascadeValues {
	int _lifeTime;
	int _emissionRate;
	glm::vec3 _point1;
	glm::vec3 _point2;
	float _angle;
	float _speed;
}

class CascadeEmitter
{

private:
	int _maxParticles;
	int _particleIndex;
	int _nextParticleToSpawn;
	int _firstActiveParticle;
	int _activeParticleCount;
	float _emissionRate;
	float _timeSinceLastemission;
	glm::vec3 _point1;
	glm::vec3 _point2;
	glm::vec3 _vect;
	glm::vec3 _spawningPos;
	glm::vec3 _acceleration;
	glm::vec3 _initialVelocity;
	float _lambda;
	float _lifeTime;

public:
	bool active;
	ParticleSystem* _particleSystem;
	CascadeEmitter(float lifeTime, float emissionRate, float elasticity);
	void SpawnParticle();
	void DespawnParticle(int i);
	void Update(float dt);
	void ToggleActive();

};

