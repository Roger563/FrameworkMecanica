#pragma once
#include <glm\glm.hpp>
#include "ParticleSystem.h"
/*namespace fountainValues {
	int _lifeTime;
	int _emissionRate;
	glm::vec3 _point;
	int _apertureAngle;
	float _speed;
}*/
class Fountain
{
	glm::vec3 _point;
	glm::vec3 _directionVector;
	int _apertureAngle;
	int _lifeTime;
	int _emissionRate;
	float _speed;
	float _timeSinceLastEmission;
	glm::vec3 _vectorDirectorAngle;
public:
	bool active;
	ParticleSystem* particleSystem;
	Fountain(float lifetime,float emissionRate,float speed, float elasticity);
	void SpawnParticle();
	void DespawnParticle(int i);
	void Update(float dt);
	void RotateDirectionVector(glm::vec3 angle);
	void OnGUIChanged(glm::vec3 point,glm::vec3 directionVectorAngle,int apertureAngle,int lifeTime,int emissionRate,float speed);
	void ToggleActive();
};

