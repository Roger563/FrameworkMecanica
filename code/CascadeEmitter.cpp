#include "CascadeEmitter.h"
#include <iostream>
#include <glm\gtx/rotate_vector.hpp>

CascadeEmitter::CascadeEmitter(float lifeTime, float emissionRate, float elasticity)
{
	
	_particleIndex = 0;
	_maxParticles = lifeTime * emissionRate;
	_lifeTime = lifeTime;
	_emissionRate = emissionRate;
	cascadeValues::_point1 = glm::vec3(-5,9.9,-5);
	cascadeValues::_point2 = glm::vec3(5,9.9,5);
	
	cascadeValues::_lifeTime = _lifeTime;
	cascadeValues::_emissionRate = _emissionRate;
	cascadeValues::_speed = 3;
	cascadeValues::_angle = 90;

	
	_particleSystem = new ParticleSystem(5000, elasticity);
	_vect =(cascadeValues::_point2 - cascadeValues::_point1);
	_lambda = 0;
	_firstActiveParticle = 0;
	_activeParticleCount = 0;
	_timeSinceLastemission = 0;
	_nextParticleToSpawn = 0;

}

void CascadeEmitter::SpawnParticle()
{
	//calculate random pos in the line
	_lambda = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1));;
	_spawningPos = glm::vec3(cascadeValues::_point1 + (_lambda * _vect));
	//starting angle
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 direction = glm::normalize(glm::cross(_vect, up));
	glm::vec3 velocity = glm::vec3(direction * cascadeValues::_speed);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(cascadeValues::_angle), glm::normalize(_vect));
	glm::vec3 velocityVect = glm::vec3(rotationMatrix * glm::vec4(velocity, 0.f));
	_particleSystem->AddParticle(_spawningPos, cascadeValues::_lifeTime,velocityVect);
	
}

void CascadeEmitter::DespawnParticle(int i)
{
	_particleSystem->eraseParticle(i);
}

void CascadeEmitter::Update(float dt)
{
	std::cout << cascadeValues::_emissionRate << std::endl;
	//spawn if need it
	float timer = (1 / (float)cascadeValues::_emissionRate);
	while (timer  <= _timeSinceLastemission) {
		SpawnParticle();
		_timeSinceLastemission -= timer;
	}
	//despawn
	for (int i = _particleSystem->GetParticlesCount()-1; i >= 0;i--) {
		if (_particleSystem->GetLifeTime(i) <= 0) {
			DespawnParticle(i);
		}
	}
	for (int i = 0; i < _particleSystem->GetParticlesCount(); i++) {	
			_particleSystem->SetLifeTime(i, (_particleSystem->GetLifeTime(i)) - dt);
		}
	_timeSinceLastemission += dt;
	_vect = cascadeValues::_point2 - cascadeValues::_point1;

}
	



