#include "ParticleSystem.h"

/////////Forward declarations
namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

ParticleSystem::ParticleSystem(int numParticles, float elasticity) 
{
	//positions = std::vector<glm::vec3>[maxParticles]; // Vector
	_elasticityCoef = elasticity;
	maxParticles = numParticles;
	for (int i = 0; i < maxParticles; i++)
	{
		fixed.push_back(false);
		positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		lastPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		velocity.push_back(glm::vec3(0.f, 0.f, 0.f));
		acceleration.push_back(glm::vec3(0.f, 0.f, 0.f));
		_lifeTime.push_back(0);
	}
}
ParticleSystem::ParticleSystem()
{
	//positions = std::vector<glm::vec3>[maxParticles]; // Vector
	_elasticityCoef = 0;
	maxParticles = 0;
	for (int i = 0; i < maxParticles; i++)
	{
		fixed.push_back(false);
		positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		lastPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		velocity.push_back(glm::vec3(0.f, 0.f, 0.f));
		acceleration.push_back(glm::vec3(0.f, 0.f, 0.f));
		_lifeTime.push_back(0);
	}
}
ParticleSystem::ParticleSystem(int numParticles, float elasticity, float mass)
{
	//positions = std::vector<glm::vec3>[maxParticles]; // Vector
	_elasticityCoef = elasticity;
	maxParticles = numParticles;
	for (int i = 0; i < maxParticles; i++)
	{
		fixed.push_back(false);
		positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		lastPositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		velocity.push_back(glm::vec3(0.f, 0.f, 0.f));
		acceleration.push_back(glm::vec3(0.f, 0.f, 0.f));
		_lifeTime.push_back(0);
	}
	_particleMass = mass;
}
;

ParticleSystem::~ParticleSystem()
{
	printf("Destruct the particle system\n");
	positions.clear();
};



void ParticleSystem::Render() {
   // int numParticles1 = ((activeParticlesFirstPosition- 1 ) + _activeParticlesCount) % maxParticles;
	//int	numParticles2 = _activeParticlesCount - numParticles1;
	
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = positions.size();
	//LilSpheres::updateParticles(activeParticlesFirstPosition, numParticles1, &(positions[0].x));
	//LilSpheres::updateParticles(0, numParticles2, &(positions[numParticles1].x));
	if(LilSpheres::particleCount>0)
	LilSpheres::updateParticles(0, LilSpheres::particleCount, &(positions[0].x));

}

void ParticleSystem::SetParticlePosition(int particleId, glm::vec3 position) {
	positions[particleId] = position;
}

void ParticleSystem::SetParticleLastPosition(int particleId, glm::vec3 position)
{
	lastPositions[particleId] = position;
}

glm::vec3 ParticleSystem::GetParticlePosition(int particleId) {
	return (positions[particleId]);
}

float ParticleSystem::GetParticleElasticity()
{
	return _elasticityCoef;
}

glm::vec3 ParticleSystem::GetParticleLastPosition(int particleId)
{
	return lastPositions[particleId];
}

std::vector<glm::vec3> ParticleSystem::GetPositions()
{
	return positions;
}

glm::vec3 ParticleSystem::GetParticleVelocity(int particleId)
{
	return velocity[particleId];
}

glm::vec3 ParticleSystem::GetParticleAcceleration(int particleId)
{
	return acceleration[particleId];
}

void ParticleSystem::SetVelocity(int particleId, glm::vec3 vel)
{
	velocity[particleId] = vel;
}

void ParticleSystem::SetLifeTime(int particleId, float lifeTime)
{
	_lifeTime[particleId] = lifeTime;
}

float ParticleSystem::GetLifeTime(int i)
{
	return _lifeTime[i];
}


void ParticleSystem::SetActiveParticleFirstPos(int firstPos)
{
	activeParticlesFirstPosition = firstPos;
}

void ParticleSystem::SetActiveParticleCount(int activeParticleCount)
{
	_activeParticlesCount = activeParticleCount;
}

void ParticleSystem::SetAcceleration(int particleId, glm::vec3 acc)
{
	acceleration[particleId] = acc;
}

void ParticleSystem::AddAcceleration(int particleId, glm::vec3 acc)
{
	acceleration[particleId] += acc;
}

void ParticleSystem::eraseParticle(int i)
{
	positions.erase(positions.begin() + i);
	lastPositions.erase(lastPositions.begin() + i);
	_lifeTime.erase(_lifeTime.begin() + i);
	velocity.erase(velocity.begin() + i);
	acceleration.erase(acceleration.begin() + i);
}

void ParticleSystem::AddParticle(glm::vec3 startingPos,float lifeTime,glm::vec3 velocityVec)
{
	positions.push_back(startingPos);
	lastPositions.push_back(startingPos);
	acceleration.push_back(glm::vec3(0.f, -9.8f, 0.f));
	velocity.push_back(velocityVec);
	_lifeTime.push_back(lifeTime);
	
}

void ParticleSystem::ApplyForce(int particleId, glm::vec3 force)
{
	glm::vec3 acceleration = force / _particleMass;
	AddAcceleration(particleId, acceleration);
}

float ParticleSystem::GetParticlesCount()
{
	return positions.size();
}

float ParticleSystem::GetMass()
{
	return _particleMass;
}

void ParticleSystem::fixParticle(int particleId)
{
	fixed[particleId] = true;
}

bool ParticleSystem::isStatic(int particleId)
{
	return fixed[particleId];
}

void ParticleSystem::AddVelocity(int particleId, glm::vec3 vel)
{
	velocity[particleId] += vel;
}
