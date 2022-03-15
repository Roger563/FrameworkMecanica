#include <glm\glm.hpp>
#include "TeleportingParticles.h";

#define ELASTICITY 0.6f
// Auxiliar methods
#pragma region auxiliar
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
    numParticles = 40;
    particles = new ParticleSystem(numParticles,ELASTICITY);
    eulerIntegrator = new EulerIntegrator(particles);
    mathematics = new Mathematics(particles);

    // NEW:
    for (int i = 0; i < numParticles; i++) {
        particles->SetVelocity(i, glm::vec3(0.0f, 0.0f, 0.0f));
        particles->SetAcceleration(i, glm::vec3(0.0f, -9.81f, 0.0f));

    }
    // ------
    for (int i = 0; i < numParticles; i++) {
        particles->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
        particles->SetParticleLastPosition(i, GetParticleInitialPosition(i, numParticles));
    }

    // Enable the rendering of particles in the framework 
    extern bool renderParticles; renderParticles = true;
}

TeleportingParticles::~TeleportingParticles() {
    delete particles;
}

void TeleportingParticles::Update(float dt) {
    // TODO implement logic to make particles fall down
    // NEW:
    eulerIntegrator->Step(dt);
    // ------

    // Check if a particle travessed the floor plane. Restart its position if it had
    mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 1, 0), 0.f));

    for (int i = 0; i < numParticles; i++) {
        particles->SetParticleLastPosition(i, particles->GetParticlePosition(i));
    }

}

void TeleportingParticles::RenderUpdate() {
    particles->Render();
}

void TeleportingParticles::RenderGui() {};

#pragma endregion