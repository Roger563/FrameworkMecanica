#pragma once
#include <glm\glm.hpp>
class Plane
{
public:
	Plane(glm::vec3 normal,float d);
	glm::vec3 GetNormal();
	float GetD();
private:
	glm::vec3 _normal;
	float _d;

};

