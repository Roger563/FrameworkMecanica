#include "Sphere_intermediate.h"

namespace Sphere {
	void setupSphere(glm::vec3, float);
	void cleanupSphere();
	void updateSphere(glm::vec3, float);
	void drawSphere();
}

Sphere_intermediate::Sphere_intermediate(glm::vec3 position, float radius)
{
	Sphere::updateSphere(position, radius);
	_position = position;
	_radius = radius;
}

glm::vec3 Sphere_intermediate::GetPosition()
{
	return _position;
}

float Sphere_intermediate::GetRadius()
{
	return _radius;
}

void Sphere_intermediate::DrawSphere_intermediate()
{
	//com la esfera es estatica no fem update
	Sphere::drawSphere();
}



void Sphere_intermediate::Update(glm::vec3 position)
{
	_position = position;
}

void Sphere_intermediate::UpdateRadius(float radius)
{
	_radius = radius;
}
