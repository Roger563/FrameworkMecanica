#include "CascadeEmitter.h"

CascadeEmitter::CascadeEmitter(float lifeTime, float emissionRate, float elasticity)
{
	_particleIndex = 0;
	_maxParticles = lifeTime * emissionRate;
	_lifeTime = lifeTime;
	_emissionRate = emissionRate;
	_particleSystem = new ParticleSystem(_maxParticles, elasticity);
	_vect = glm::normalize(_point2 - _point1);
	_lambda = 0;
	_firstActiveParticle = 0;
	_activeParticleCount = 0;
	_timeSinceLastemission = 0;
	_nextParticleToSpawn = 0;

}

void CascadeEmitter::SpawnParticle()
{
	//calculate random pos in the line
	_lambda = rand() % 1;
	_spawningPos = glm::vec3(_point1 + (_lambda * _vect));
	//setup the particle
	_particleSystem->SetAcceleration(_nextParticleToSpawn, _acceleration);
	_particleSystem->SetVelocity(_nextParticleToSpawn, _initialVelocity);
	_particleSystem->SetParticlePosition(_nextParticleToSpawn, _spawningPos);
	_particleSystem->SetParticleLastPosition(_nextParticleToSpawn, _spawningPos);
	_particleSystem->SetLifeTime(_nextParticleToSpawn, _lifeTime);
	//activate
	_particleSystem->SetActive(_nextParticleToSpawn, true);
	//we add one to the starting pos
	_nextParticleToSpawn++;
	_nextParticleToSpawn = _nextParticleToSpawn % _maxParticles;
	_activeParticleCount++;
	_particleSystem->SetActiveParticleCount(_activeParticleCount);
}

void CascadeEmitter::DespawnParticle(int index)
{
	_activeParticleCount--;
	_particleSystem->SetActiveParticleCount(_activeParticleCount);
	_firstActiveParticle++;
	_firstActiveParticle = _firstActiveParticle % _maxParticles;
	_particleSystem->SetActiveParticleFirstPos(_firstActiveParticle);
	//set active false
	_particleSystem->SetActive(index, false);
}

void CascadeEmitter::Update(float dt)
{
	//spawn if need it
	if ( (_lifeTime / _emissionRate)  <= _timeSinceLastemission) {
		SpawnParticle();
		_timeSinceLastemission = 0;
	}
	//despawn
	for (int i = 0; i < _maxParticles; i++) {
		if (_particleSystem->IsActive(i)) {

			if (_particleSystem->GetLifeTime(i) <= 0) {
				DespawnParticle(i);
			}
			_particleSystem->SetLifeTime(i, *(_particleSystem->GetLifeTime(i)) + dt);
		}
	}
	//timers
	_timeSinceLastemission += dt;
}


