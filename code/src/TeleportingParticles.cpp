#include <glm\glm.hpp>
#include "TeleportingParticles.h";


#define ELASTICITY 0.6f
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
    x = z = -5.f + margin + id * offset;
    y = 9.9f;

    return glm::vec3(x, y, z);
}



#pragma endregion

#pragma region class
TeleportingParticles::TeleportingParticles() {
    renderSphere = true;
    numParticles = 40;
    particles = new ParticleSystem(numParticles,ELASTICITY);
    eulerIntegrator = new EulerIntegrator(particles);
    mathematics = new Mathematics(particles);
    sphere = new Sphere_intermediate(glm::vec3(1, 5, 0), 2.f);
    // NEW:
    for (int i = 0; i < numParticles; i++) {
        particles->SetVelocity(i, glm::vec3(0.0f, 0.0f, 0.0f));
        particles->SetAcceleration(i, glm::vec3(ACCELERATION_X, ACCELERATION_Y, ACCELERATION_Z));

    }
    // ------
    for (int i = 0; i < numParticles; i++) {
        particles->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
        particles->SetParticleLastPosition(i, GetParticleInitialPosition(i, numParticles));
    }

    // Enable the rendering of particles in the framework 
    extern bool renderParticles; renderParticles = true;

    // ------
}

TeleportingParticles::~TeleportingParticles() {
    renderSphere = false;
    delete particles;
}

void TeleportingParticles::Update(float dt) {
    // NEW:
    eulerIntegrator->Step(dt);
    // ------

    // Check if a particle travessed the floor plane. Restart its position if it had
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 1, 0), 0.f)); // DOWN
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, -1, 0), 10.f)); // UP
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(1, 0, 0), 5.f)); // X NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(-1, 0, 0), 5.f)); // X POSITIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, 1), 5.f)); // Z NEGATIVE
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, -1), 5.f)); // Z POSITIVE

    mathematics->GetSphereCollisionPlane(sphere); // sphere

    for (int i = 0; i < numParticles; i++) {
        particles->SetParticleLastPosition(i, particles->GetParticlePosition(i));
    }
}

void TeleportingParticles::RenderUpdate() {
    particles->Render();
    sphere->DrawSphere_intermediate();
}

void TeleportingParticles::RenderGui() {};

#pragma endregion