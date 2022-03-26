#include "ParticleSystem.h"

/////////Forward declarations
namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

ParticleSystem::ParticleSystem(int numParticles,float elasticity) : maxParticles(numParticles)
{
	positions = new std::vector<glm::vec3>[maxParticles]; // Vector
	lastPositions = new glm::vec3[maxParticles]; // Array
	velocity = new glm::vec3[maxParticles];
	acceleration = new glm::vec3[maxParticles];
	_active = new bool[maxParticles];
	_lifeTime = new float[maxParticles];
	_elasticityCoef = elasticity;

	for (int i = 0; i < maxParticles; i++)
	{
		positions->push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Vector
		lastPositions[i] = glm::vec3(0.f, 0.f, 0.f); // Array
		velocity[i] = glm::vec3(0.f, 0.f, 0.f);
		acceleration[i] = glm::vec3(0.f, 0.f, 0.f);
		_active[i] = false;
		_lifeTime[i] = 0;
	}
};

ParticleSystem::~ParticleSystem() {
	printf("Destruct the particle system\n");
	delete positions;
};

int ParticleSystem::GetNumberOfParticles() {
	return maxParticles;
};

void ParticleSystem::Render() {
    int numParticles1 = ((activeParticlesFirstPosition- 1 ) + _activeParticlesCount) % maxParticles;
	int	numParticles2 = _activeParticlesCount - numParticles1;
	
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = GetNumberOfParticles();
	//LilSpheres::updateParticles(activeParticlesFirstPosition, numParticles1, &(positions[0].x));
	//LilSpheres::updateParticles(0, numParticles2, &(positions[numParticles1].x));
	LilSpheres::updateParticles(0, GetNumberOfParticles(), &(positions[0]));

}

void ParticleSystem::SetParticlePosition(int particleId, glm::vec3 position) {
	positions[particleId] = position;
}

void ParticleSystem::SetParticleLastPosition(int particleId, glm::vec3 position)
{
	lastPositions[particleId] = position;
}

glm::vec3 ParticleSystem::GetParticlePosition(int particleId) {
	return positions[particleId];
}

float ParticleSystem::GetParticleElasticity()
{
	return _elasticityCoef;
}

glm::vec3 ParticleSystem::GetParticleLastPosition(int particleId)
{
	return lastPositions[particleId];
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

float* ParticleSystem::GetLifeTime(int particleId)
{
	return _lifeTime;
}

void ParticleSystem::SetActive(int particleId, bool active)
{
	_active[particleId] = active;
}

bool ParticleSystem::IsActive(int particleId)
{
	return _active;
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