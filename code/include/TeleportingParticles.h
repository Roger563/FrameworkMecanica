#pragma once
#pragma once

#include "Simulator.h";
#include "ParticleSystem.h"
#include "EulerIntegrator.h"
#include "Mathematics.h"

class TeleportingParticles : public Simulator {
public:
	TeleportingParticles();
	~TeleportingParticles();

	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
private:
	ParticleSystem* particles;
	EulerIntegrator* eulerIntegrator;
	Mathematics* mathematics;
	int numParticles;
};