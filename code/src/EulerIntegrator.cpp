#include "EulerIntegrator.h"

EulerIntegrator::EulerIntegrator(ParticleSystem* ps)
{
	_ps = ps;
}

void EulerIntegrator::Step(float dt)
{
	for (int i = 0; i < _ps->GetParticlesCount(); i++)
	{
		_ps->SetParticlePosition(i, CalculatePosition(i, dt));
		_ps->SetVelocity(i, CalculateVelocity(i, dt));
	}
}

glm::vec3 EulerIntegrator::CalculatePosition(int index,float dt)
{
	return _ps->GetParticlePosition(index) + _ps->GetParticleVelocity(index) * dt;
}

glm::vec3 EulerIntegrator::CalculateVelocity(int index,float dt)
{
	return _ps->GetParticleVelocity(index) + _ps->GetParticleAcceleration(index) * dt;
}
