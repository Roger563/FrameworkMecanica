#include "Capsule_intermediate.h"


Capsule_intermediate::Capsule_intermediate(glm::vec3 center1, glm::vec3 center2, float radius)
{
	_center1 = center1;
	_center2 = center2;
	_radius = radius;
	CapsuleValues::_center1 = _center1;
	CapsuleValues::_center2 = _center2;
	CapsuleValues::_radius = _radius;
}

glm::vec3 Capsule_intermediate::GetCenter1()
{
	return _center1;
}

glm::vec3 Capsule_intermediate::GetCenter2()
{
	return _center2;
}

float Capsule_intermediate::GetRadious()
{
	return _radius;
}

void Capsule_intermediate::Update(glm::vec3 center2)
{
	_center1 = CapsuleValues::_center1;
	_center2 = CapsuleValues::_center2;
	_radius = CapsuleValues::_radius;
}
