#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>

#include "RandomStaticParticles.h"
#include "TeleportingParticles.h"


#pragma region simulationSelection
enum class EnabledSimulation {
	RANDOM_STATIC_PARTICLES,
	TELEPORTING_PARTICLES,
};

Simulator* currentSimulator;
EnabledSimulation currentSimulation;
void setSimulation(EnabledSimulation simulation) {
	if (currentSimulation == simulation) {
		return;
	}

	delete currentSimulator;
	currentSimulation = simulation;
	switch (simulation) {
		case EnabledSimulation::RANDOM_STATIC_PARTICLES:
			printf("Start the random particles simulation");
			currentSimulator = new RandomStaticParticles();
			break;
		;;
		case EnabledSimulation::TELEPORTING_PARTICLES:
			printf("Start the teleporting particles");
			currentSimulator = new TeleportingParticles();
			break;
		;;
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;
void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Simulation")) {
			if (ImGui::MenuItem("RandomStaticParticles")) { setSimulation(EnabledSimulation::RANDOM_STATIC_PARTICLES); };
			if (ImGui::MenuItem("TeleportingParticles")) { setSimulation(EnabledSimulation::TELEPORTING_PARTICLES); };

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Physics Parameters", &show, 0);
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		currentSimulator->RenderGui();
	}
	
	ImGui::End();
}

#pragma endregion


void PhysicsInit() {
	// The default simulation
	currentSimulator = new RandomStaticParticles();
	currentSimulation = EnabledSimulation::RANDOM_STATIC_PARTICLES;
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}