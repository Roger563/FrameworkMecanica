#pragma once

#include "Simulator.h";
#include "Capsule_intermediate.h"
#include "ParticleSystem.h"
#include "EulerIntegrator.h"
#include "Mathematics.h"
#include "Sphere_intermediate.h"
#include "Gui.h"
#include "CascadeEmitter.h"
#include "../Fountain.h"


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
	EulerIntegrator* eulerIntegratorCascade;
	EulerIntegrator* eulerIntegratorFountain;
	Mathematics* mathematics;
	int numParticles;
	Fountain* fountain;
	Gui* gui;
};