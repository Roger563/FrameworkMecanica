#pragma once

#include <glm\glm.hpp>

#include <vector>

class ParticleSystem {
public:
	
	ParticleSystem(int numParticles,float elasticity);
	ParticleSystem();
	ParticleSystem(int numParticles,float elasticity,float mass);
	~ParticleSystem();

	void Render();
	void SetParticlePosition(int particleId, glm::vec3 position);
	void SetParticleLastPosition(int particleId, glm::vec3 position);
	glm::vec3 GetParticlePosition(int particleId);
	float GetParticleElasticity();
	glm::vec3 GetParticleLastPosition(int particleId);
	std::vector<glm::vec3> GetPositions();
	glm::vec3 GetParticleVelocity(int particleId);
	glm::vec3 GetParticleAcceleration(int particleId);
	void SetVelocity(int particleId, glm::vec3 vel);
	//LifeTime
	void SetLifeTime(int particleId, float lifeTime);
	float GetLifeTime(int i);
	//active state
	void SetActiveParticleFirstPos(int firstPos);
	void SetActiveParticleCount(int activeParticleCount);
	void SetAcceleration(int particleId, glm::vec3 acc);
	void AddAcceleration(int particleId, glm::vec3 acc);
	void eraseParticle(int i);
	void AddParticle(glm::vec3 startingPos,float lifeTime, glm::vec3 velocityVec);
	void ApplyForce(int particleId, glm::vec3 force);
	float GetParticlesCount();
	float GetMass();
	void fixParticle(int particleId);
	bool isStatic(int particleId);
	void AddVelocity(int particleId, glm::vec3 vel);
private:
	std::vector<bool> fixed;
	int maxParticles;
	int _activeParticlesCount;
	int activeParticlesFirstPosition;
	float _particleMass;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> lastPositions;
	std::vector<float> _lifeTime;
	std::vector<glm::vec3> velocity;
	std::vector<glm::vec3> acceleration;
	float _elasticityCoef;
};