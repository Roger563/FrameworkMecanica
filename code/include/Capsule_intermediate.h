#pragma once
#include <glm\glm.hpp>

namespace CapsuleValues {

	glm::vec3 _center1;
	glm::vec3 _center2;
	float _radius;

}

class Capsule_intermediate
{
private:

	glm::vec3 _center1;
	glm::vec3 _center2;
	float _radius;

public:
	bool active;
	Capsule_intermediate(glm::vec3 center1, glm::vec3 center2, float radius);
	glm::vec3 GetCenter1();
	glm::vec3 GetCenter2();
	float GetRadious();
	void Update(glm::vec3 center2);
};

