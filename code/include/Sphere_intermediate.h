#pragma once

#include <glm\glm.hpp>

class Sphere_intermediate
{
private:

	glm::vec3 _position;
	float radius;

public:

	Sphere_intermediate(glm::vec3 _position, float radius);

	void DrawSphere_intermediate();
};

