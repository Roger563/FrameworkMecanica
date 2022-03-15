#pragma once

#include <glm\glm.hpp>

class ParticleSystem {
public:
	ParticleSystem(int maxParticles,float elasticity);
	~ParticleSystem();
	int GetNumberOfParticles();

	void Render();
	void SetParticlePosition(int particleId, glm::vec3 position);
	void SetParticleLastPosition(int particleId, glm::vec3 position);
	glm::vec3 GetParticlePosition(int particleId);
	float GetParticleElasticity();
	glm::vec3 GetParticleLastPosition(int particleId);
	glm::vec3 GetParticleVelocity(int particleId);
	glm::vec3 GetParticleAcceleration(int particleId);
	void SetVelocity(int particleId, glm::vec3 vel);
	void SetAcceleration(int particleId, glm::vec3 acc);
private:
	int maxParticles;
	glm::vec3* positions;
	glm::vec3* lastPositions;
	glm::vec3* velocity;
	glm::vec3* acceleration;
	float _elasticityCoef;
};