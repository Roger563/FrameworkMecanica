#pragma once

#include "Simulator.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include "../include/Sphere_intermediate.h"
#include "../include/Capsule_intermediate.h"
#include"../Fountain.h"

namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius);
}
namespace Capsule {
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
}
namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx, particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
namespace cascadeValues {
	extern int _lifeTime;
	extern int _emissionRate;
	extern glm::vec3 _point1;
	extern glm::vec3 _point2;
	extern float _angle;
	extern float _speed;
}



extern bool renderSphere, renderCapsule, renderParticles;


class Gui : public Simulator {
private:
	glm::vec3 sphereCenter;
	glm::vec3 capsuleA;
	glm::vec3 capsuleB;
	bool guiCapsuleChanged;
	Sphere_intermediate* sphereCollider;
	Capsule_intermediate* capsuleCollider;
	bool toggleActivity;
	bool lastToggleActivityState;
	//fountain
	Fountain* fountain;
	glm::vec3 fountainPoint;
	glm::vec3 fountainDirectorVectorAngle;
	int fountainApertureAngle;
	int fountainLifeTime;
	int fountainEmissionRate;
	int fountainSpeed;

	enum Movement {
		LEFT,
		STOP,
		RIGHT,
	};

	int sphereMovement;  // Int perque, tot i ser Movement, ho farem servir a la GUI

public:
	Gui(Sphere_intermediate* sphere, Capsule_intermediate* capsule,Fountain* _fountain) {
		sphereCollider = sphere;
		capsuleCollider = capsule;
		fountain = _fountain;
		sphereCenter = glm::vec3(0.f, 2.f, 0.f);
		sphereCollider->Update(sphereCenter);
		capsuleA = glm::vec3(0.f, 1.f, 0.f);
		capsuleB = glm::vec3(1.f, 1.f, 2.f);
		sphereMovement = Movement::STOP;
		lastToggleActivityState = toggleActivity;
		fountainPoint = glm::vec3(0, 5, 0);
		fountainDirectorVectorAngle = glm::vec3(0, 0, 0);
		fountainApertureAngle = 30;
		fountainLifeTime = 2;
		fountainEmissionRate = 200;
		fountainSpeed = 2;

		for (int i = 0; i < LilSpheres::maxParticles; i++) {
			float x = -5.f + (float)rand() / (RAND_MAX / 10.f);
			float y = 0.f + (float)rand() / (RAND_MAX / 10.f);
			float z = -5.f + (float)rand() / (RAND_MAX / 10.f);

			glm::vec3 pos = glm::vec3(x, y, z);
			LilSpheres::updateParticles(i, 1, &pos.x); //POC EFICIENT; PERO DEMOSTRA COM ACTUALITZAR NOMES CERTES PARTICULES
		}
	}
	void Update(float dt) {
		if (renderSphere) {
			switch (sphereMovement) {
			case Movement::LEFT:
				sphereCenter.x -= 0.3f;
				break;
			case Movement::RIGHT:
				sphereCenter.x += 0.3f;	
				break;
			}
		}
		if (sphereCollider->GetPosition() != sphereCenter) {
			sphereCollider->Update(sphereCenter);
		}

		capsuleCollider->Update(capsuleA, capsuleB);
		fountain->OnGUIChanged(fountainPoint, fountainDirectorVectorAngle, fountainApertureAngle, fountainLifeTime, fountainEmissionRate, fountainSpeed);

	};

	void RenderUpdate() {
		sphereCollider->Update((glm::vec3(sphereCenter.x, sphereCenter.y, sphereCenter.z)));
		sphereCollider->UpdateRadius(1);
		Sphere::updateSphere(sphereCenter, 1.f);


		if (guiCapsuleChanged) Capsule::updateCapsule(capsuleA,capsuleB , 1.f);
		
		
	}

	void RenderGui() {
		guiCapsuleChanged = false;

		ImGui::Checkbox("Show particles", &renderParticles);
		ImGui::Checkbox("Show sphere", &renderSphere);
		ImGui::Checkbox("Change Emitter", &toggleActivity);
		if (toggleActivity!= lastToggleActivityState) {
			fountain->ToggleActive();
			lastToggleActivityState = toggleActivity;
		}
		
		guiCapsuleChanged |= ImGui::Checkbox("Show capsule", &renderCapsule);

		if (renderParticles) {
			/*ImGui::SliderInt(
				"First particle", //label
				&LilSpheres::firstParticleIdx, // where the value exists
				0, // min
				LilSpheres::maxParticles // max
			);*/
			if (ImGui::CollapsingHeader("Cascade")) {
				ImGui::SliderFloat3(
					"cascade Point1",
					&cascadeValues::_point1.x, // pointer to an array of 3 floats
					-5.0f, // min
					10.0f // max
				);
				ImGui::SliderFloat3(
					"cascade Point2",
					&cascadeValues::_point2.x, // pointer to an array of 3 floats
					-5.0f, // min
					10.0f // max
				);
				ImGui::SliderInt(
					"cascade lifeTime", //label
					&cascadeValues::_lifeTime, // where the value exists
					1, // min
					10 // max
				);
				ImGui::SliderFloat(
					"cascade angle", //label
					&cascadeValues::_angle, // where the value exists
					1, // min
					360 // max
				);
				ImGui::SliderFloat(
					"cascade Initial speed ", //label
					&cascadeValues::_speed, // where the value exists
					0.5, // min
					20 // max
				);
				ImGui::SliderInt(
					"cascade EmissionRate", //label
					&cascadeValues::_emissionRate, // where the value exists
					0, // min
					2000 // max
				);
			}
			/*ImGui::DragInt(
				"Number of particles", //label
				&LilSpheres::particleCount, // where the value exists
				1.f, // drag speed
				0, // min
				LilSpheres::maxParticles // max
			);*/
			//fountain
			if (ImGui::CollapsingHeader("Fountain")) {
				ImGui::SliderFloat3(
					"fountain centerPoint",
					&fountainPoint.x,
					-5,
					10
				);
				ImGui::SliderFloat3(
					"fountain rotation angle",
					&fountainDirectorVectorAngle.x,
					0,
					360
				);

				ImGui::SliderInt(
					"fountain aperture angle",
					&fountainApertureAngle, // pointer to an array of 3 floats
					10, // drag speed
					360 // min
				);
				ImGui::SliderInt(
					"fountain life Time",
					&fountainLifeTime, // pointer to an array of 3 floats
					1, // min
					10 // max
				);
				ImGui::SliderInt(
					"fountain Emission Rate",
					&fountainEmissionRate, // pointer to an array of 3 floats
					0, // min
					2000 // max
				);
				ImGui::SliderInt(
					"fountain Speed",
					&fountainSpeed, // pointer to an array of 3 floats
					1, // min
					10 // max
				);
			}
		}

		if (renderSphere) {
			ImGui::SliderFloat3(
				"Sphere center",
				&sphereCenter.x,
				-5,
				10// pointer to an array of 3 floats
			);
			

			ImGui::RadioButton("Move left", &sphereMovement, Movement::LEFT);
			ImGui::RadioButton("STOP", &sphereMovement, Movement::STOP);
			ImGui::RadioButton("Move right", &sphereMovement, Movement::RIGHT);

			if (ImGui::Button("Reset sphere")) {
				sphereCenter = glm::vec3(0.f, 1.f, 0.f);
			}
			
			sphereCollider->active = true;
		
		}
		else {
			sphereCollider->active = false;

		}

		if (renderCapsule) {
			capsuleCollider->active = true;
			guiCapsuleChanged |= ImGui::SliderFloat3(
				"Capsule A",
				&capsuleA.x,
				-5.f,
				10.f
			);

			guiCapsuleChanged |= ImGui::SliderFloat3(
				"Capsule B",
				&capsuleB.x,
				-5.f,
				10.f
			);
			/*ImGui::SliderFloat(
				"capsule point 1.x", //label
				&CapsuleValues::_center1.x , // where the value exists
				1, // min
				10 // max
			);
			ImGui::SliderFloat(
				"capsule point 1.y", //label
				&CapsuleValues::_center1.y, // where the value exists
				1, // min
				10 // max
			);
			ImGui::SliderFloat(
				"capsule point 1.z", //label
				&CapsuleValues::_center1.z, // where the value exists
				1, // min
				10 // max
			);*/
		}
		else {
			capsuleCollider->active = false;

		}
	}

	~Gui() {
		renderParticles = false;
		renderSphere = false;
		renderCapsule = false;
	}
};

