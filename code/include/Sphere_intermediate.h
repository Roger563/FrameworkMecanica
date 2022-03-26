#pragma once

#include <glm\glm.hpp>

class Sphere_intermediate
{
private:

	glm::vec3 _position;
	float _radius;
	

public:
	bool active;
	Sphere_intermediate(glm::vec3 _position, float radius);
	glm::vec3 GetPosition();
	float GetRadius();
	void DrawSphere_intermediate();

	void Update(glm::vec3 position);
	void UpdateRadius(float radius);
};

