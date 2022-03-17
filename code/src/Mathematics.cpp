#include "Mathematics.h"


Mathematics::Mathematics(ParticleSystem* ps)
{
    _ps = ps;
}

Plane* Mathematics::GetPlane(glm::vec3 point, glm::vec3 normal)
{
    return new Plane(normal, -(point.x * normal.x + point.y * normal.y + point.z * normal.z));
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

bool Mathematics::HasCollidedWithSphere(Sphere_intermediate* sphere, glm::vec3 point)
{
    glm::vec3 pc = point - sphere->GetPosition();
    float magnitude = sqrt(pow(pc.x,2) + pow(pc.y,2) + pow(pc.z,2));
    return magnitude < sphere->GetRadius();;
}

void Mathematics::GetSphereCollisionPlane(Sphere_intermediate* sphere)
{
    for (int i = 0; i < _ps->GetNumberOfParticles(); i++)
    {
        if (HasCollidedWithSphere(sphere, _ps->GetParticlePosition(i))) {

            glm::vec3 LP = _ps->GetParticlePosition(i) - _ps->GetParticleLastPosition(i);
            glm::vec3 v = Normalize(LP);

            // in the 2nd grade equation :
            //a=v dot v
            //b= 2(XdotV - VdotC)
            //c = (X-C) DOT (X-C) - POW(R,2)
            float a = glm::dot(v, v);
            float b = 2 * (glm::dot(_ps->GetParticlePosition(i), v) - glm::dot(v, sphere->GetPosition()));
            float c = glm::dot((_ps->GetParticlePosition(i) - sphere->GetPosition()), (_ps->GetParticlePosition(i) - sphere->GetPosition())) - pow(sphere->GetRadius(), 2);

            //-b +- sqr(pow(b,2)-4*a*c)   / 2a 

            float result  = (-b + sqrt(pow(b, 2) - (double)4.0f * a * c)) / 2.0f;
            float result2 = (-b - sqrt(pow(b, 2) - (double)4.0f * a * c)) / 2.0f;
            float lambda;
            //check lamdas-> DUBTE
            if (sqrt(pow(result, 2) < sqrt(pow(result2, 2)))) {
                lambda = result;
            }
            else {
                lambda = result2;
            }
            //substitute landa on the line equation:
            glm::vec3 intersectionPoint = _ps->GetParticlePosition(i) + lambda * v;

            glm::vec3 planeNormal = Normalize((intersectionPoint - sphere->GetPosition()));
            //
            Plane* plane = GetPlane(intersectionPoint, planeNormal);
            Collide(plane, i);
        }
    }
}

glm::vec3 Mathematics::Normalize(glm::vec3 vec)
{
    float magnitude = sqrt(pow(vec.x,2) + pow(vec.y,2) + pow(vec.z,2));
    glm::vec3 normalizedVec = glm::vec3(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude);
    return normalizedVec;
}






