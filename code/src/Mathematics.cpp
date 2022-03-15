#include "Mathematics.h"


Mathematics::Mathematics(ParticleSystem* ps)
{
    _ps = ps;
}

Plane* Mathematics::GetPlane(glm::vec3 point, glm::vec3 normal)
{
    return new Plane(normal, (point.x * normal.x + point.y * normal.y + point.z * normal.z));
}

Plane* Mathematics::GetPlane(glm::vec3 point, glm::vec3 vec1, glm::vec3 vec2)
{
    return nullptr;
}

void Mathematics::CheckCollisionWithPlane(Plane* plane)
{
    for (int i = 0; i < _ps->GetNumberOfParticles(); i++)
    {
        if ( ((glm::dot(plane->GetNormal(), _ps->GetParticleLastPosition(i)) + plane->GetD()) *(glm::dot(plane->GetNormal(), _ps->GetParticlePosition(i)) + plane->GetD()) ) <= 0){
            Collide(plane,i);
        }
    }
}

void Mathematics::Collide(Plane* plane,int index)
{
    _ps->SetParticlePosition( index,_ps->GetParticlePosition(index)-(1+_ps->GetParticleElasticity())*(glm::dot(plane->GetNormal(), _ps->GetParticlePosition(index)) + plane->GetD())* plane->GetNormal());
    _ps->SetVelocity( index,_ps->GetParticleVelocity(index)-(1+_ps->GetParticleElasticity())*(glm::dot(plane->GetNormal(),_ps->GetParticleVelocity(index)))* plane->GetNormal());
}
