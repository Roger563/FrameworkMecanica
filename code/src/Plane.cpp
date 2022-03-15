#include "Plane.h"

Plane::Plane(glm::vec3 normal, float d)
{
    _normal = normal;
    _d = d;
}

glm::vec3 Plane::GetNormal()
{
    return _normal;
}

float Plane::GetD()
{
    return _d;
}
