#include "Sphere_intermediate.h"

namespace Sphere {
	void setupSphere(glm::vec3, float);
	void cleanupSphere();
	void updateSphere(glm::vec3, float);
	void drawSphere();
}

Sphere_intermediate::Sphere_intermediate(glm::vec3 _position, float radius)
{
	Sphere::setupSphere(_position, radius);
}
