#include "Fountain.h"
#include <glm\gtx/rotate_vector.hpp>
Fountain::Fountain(float lifetime, float emissionRate, float speed,float elasticity)
{
	active = true;
	_lifeTime = lifetime;
	_emissionRate = emissionRate;
	_speed = speed;
	_point = glm::vec3(0, 5, 0);
	_directionVector = glm::vec3(0, 1, 0);
	_vectorDirectorAngle = glm::vec3(0, 0, 0);
	_apertureAngle = 30;
	particleSystem = new ParticleSystem(5000,elasticity);
	_timeSinceLastEmission = 0;
}

void Fountain::SpawnParticle()
{
	//random dir
	glm::vec3 angle;
	if (rand() % 2 == 1) { angle.x = (rand() % _apertureAngle);}
	else{ angle.x = -(rand() % _apertureAngle); }

	if (rand() % 2 == 1) { angle.y = (rand() % _apertureAngle); }
	else { angle.y = -(rand() % _apertureAngle); }

	if (rand() % 2 == 1) { angle.z = (rand() % _apertureAngle); }
	else { angle.z = -(rand() % _apertureAngle); }

	glm::vec3 particleDir = _directionVector;
	particleDir = glm::rotate(glm::mat4(), glm::radians(angle.x), glm::vec3(1, 0, 0)) * glm::vec4(particleDir,0);
	particleDir = glm::rotate(glm::mat4(), glm::radians(angle.y), glm::vec3(0, 1, 0)) * glm::vec4(particleDir,0);
	particleDir = glm::rotate(glm::mat4(), glm::radians(angle.z), glm::vec3(0, 0, 1)) * glm::vec4(particleDir,0);
	
	particleSystem->AddParticle(_point, _lifeTime, particleDir*_speed);
}

void Fountain::DespawnParticle(int i)
{
	particleSystem->eraseParticle(i);
}

void Fountain::Update(float dt)
{
	//spawn if need it
	float timer = (1 / (float)_emissionRate);
	while (timer <= _timeSinceLastEmission) {
		SpawnParticle();
		_timeSinceLastEmission -= timer;
	}
	//despawn
	for (int i = particleSystem->GetParticlesCount() - 1; i >= 0; i--) {
		if (particleSystem->GetLifeTime(i) <= 0) {
			DespawnParticle(i);
		}
	}
	for (int i = 0; i < particleSystem->GetParticlesCount(); i++) {
		particleSystem->SetLifeTime(i, (particleSystem->GetLifeTime(i)) - dt);
	}
	_timeSinceLastEmission += dt;
	//_vect = fountainValues::_point2 - fountainValues::_point1;
}

void Fountain::RotateDirectionVector(glm::vec3 angle)
{
	_vectorDirectorAngle = angle;
	_directionVector = glm::vec3(0, 1, 0);
	_directionVector = glm::rotate(glm::mat4(), glm::radians(_vectorDirectorAngle.x), glm::vec3(1, 0, 0)) * glm::vec4(_directionVector, 0);
	_directionVector = glm::rotate(glm::mat4(), glm::radians(_vectorDirectorAngle.y), glm::vec3(0, 1, 0)) * glm::vec4(_directionVector, 0);
	_directionVector = glm::rotate(glm::mat4(), glm::radians(_vectorDirectorAngle.z), glm::vec3(0, 0, 1)) * glm::vec4(_directionVector, 0);
	
}

void Fountain::OnGUIChanged(glm::vec3 point, glm::vec3 directionVectorAngle, int apertureAngle, int lifeTime, int emissionRate, float speed)
{
	_point = point;
	_apertureAngle = apertureAngle;
	_lifeTime = lifeTime;
	_emissionRate = emissionRate;
	_speed = speed;
	if(_vectorDirectorAngle!= directionVectorAngle)
	RotateDirectionVector(directionVectorAngle);
}

void Fountain::ToggleActive()
{
	active = !active;
}
