#include <glm\glm.hpp>
#include "TeleportingParticles.h";

#define ELASTICITY 0.3f
#define ACCELERATION_X 0.f
#define ACCELERATION_Y -9.8f
#define ACCELERATION_Z 0.f

// TODO: Posar el bool de renderització de l'esfera a true al principi de TeleportingParticles.

// Auxiliar methods
#pragma region auxiliar

//global variables:
extern bool renderSphere;
extern bool renderCapsule;
Sphere_intermediate* sphere;

glm::vec3 GetParticleInitialPosition(int id, int numParticles) {
    float margin = 0.1f;
    float available_length = 2 * (5.f - margin);
    float offset = available_length / (numParticles - 1);

    float x, y, z;
    x = /*z = */-5.f + margin + id * offset;
    y = 9.9f;
    z = 0; 
    return glm::vec3(x, y, z);
}



#pragma endregion
#pragma region class
TeleportingParticles::TeleportingParticles() {
    
    renderSphere = true;
    numParticles = 1000;
    cascade = new CascadeEmitter(1,1,ELASTICITY);
    eulerIntegratorCascade = new EulerIntegrator(cascade->_particleSystem);
    
    mathematics = new Mathematics();
    capsule = new Capsule_intermediate(glm::vec3(-5, 5, 0), glm::vec3(0, 0, 0),1.0f);
    sphere = new Sphere_intermediate(glm::vec3(1, 5, 0), 2.f);
    fountain = new Fountain(2, 200, 5, ELASTICITY);
    eulerIntegratorFountain = new EulerIntegrator(fountain->particleSystem);
    gui = new Gui(sphere,capsule,fountain);
    // NEW:
    for (int i = 0; i < numParticles; i++) {
       // cascade->_particleSystem->SetVelocity(i, glm::vec3(0.0f, 0.0f, 0.0f));
        //cascade->_particleSystem->SetAcceleration(i, glm::vec3(ACCELERATION_X, ACCELERATION_Y, ACCELERATION_Z));

    }
    // ------
    for (int i = 0; i < numParticles; i++) {
       // cascade->_particleSystem->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
        //cascade->_particleSystem->SetParticleLastPosition(i, GetParticleInitialPosition(i, numParticles));
    }

    // Enable the rendering of particles in the framework 
    extern bool renderParticles; renderParticles = true;

    // ------
}

TeleportingParticles::~TeleportingParticles() {
    renderSphere = false;
    delete cascade;
}

void TeleportingParticles::Update(float dt) {
    gui->Update(dt);
    cascade->Update(dt);
    fountain->Update(dt);
    // NEW:
    eulerIntegratorCascade->Step(dt);
    eulerIntegratorFountain->Step(dt);
    // ------
    
    //Cascade
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 1, 0), 0.f),cascade->_particleSystem); // DOWN
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, -1, 0), 10.f),cascade->_particleSystem); // UP
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(1, 0, 0), 5.f),cascade->_particleSystem); // X NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(-1, 0, 0), 5.f),cascade->_particleSystem); // X POSITIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, 1), 5.f),cascade->_particleSystem); // Z NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, -1), 5.f),cascade->_particleSystem); // Z POSITIVE
    if (capsule->active) {
        mathematics->CheckCollisionWithCapsule(capsule->GetCenter1(), capsule->GetCenter2(), capsule->GetRadious(), cascade->_particleSystem);
    }
    mathematics->GetSphereCollisionPlane(sphere, cascade->_particleSystem); // sphere
    for (int i = 0; i < cascade->_particleSystem->GetParticlesCount(); i++) {
        cascade->_particleSystem->SetParticleLastPosition(i, cascade->_particleSystem->GetParticlePosition(i));
    }
    //Fountain
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 1, 0), 0.f), fountain->particleSystem); // DOWN
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, -1, 0), 10.f), fountain->particleSystem); // UP
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(1, 0, 0), 5.f), fountain->particleSystem); // X NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(-1, 0, 0), 5.f), fountain->particleSystem); // X POSITIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, 1), 5.f), fountain->particleSystem); // Z NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, -1), 5.f), fountain->particleSystem); // Z POSITIVE
    if (capsule->active) {
        mathematics->CheckCollisionWithCapsule(capsule->GetCenter1(), capsule->GetCenter2(), capsule->GetRadious(), fountain->particleSystem);
    }
    mathematics->GetSphereCollisionPlane(sphere, fountain->particleSystem); // sphere
    for (int i = 0; i < fountain->particleSystem->GetParticlesCount(); i++) {
        fountain->particleSystem->SetParticleLastPosition(i, fountain->particleSystem->GetParticlePosition(i));
    }
}

void TeleportingParticles::RenderUpdate() {
    gui->RenderUpdate();
    if (!fountain->active) {
        cascade->_particleSystem->Render();
    }
    else {
        fountain->particleSystem->Render();
    }
    sphere->DrawSphere_intermediate();
}

void TeleportingParticles::RenderGui() {
    gui->RenderGui();
};

#pragma endregion