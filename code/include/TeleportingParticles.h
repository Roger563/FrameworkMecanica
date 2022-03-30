#pragma once
#pragma once

#include "Simulator.h";
#include "Capsule_intermediate.h"
#include "ParticleSystem.h"
#include "EulerIntegrator.h"
#include "Mathematics.h"
#include "Sphere_intermediate.h"
#include "Gui.h"
#include "CascadeEmitter.h"

class TeleportingParticles : public Simulator {
public:
	TeleportingParticles();
	~TeleportingParticles();

	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
	CascadeEmitter* cascade;
private:
	Capsule_intermediate* capsule;
	EulerIntegrator* eulerIntegrator;
	Mathematics* mathematics;
	int numParticles;
	Gui* gui;
};