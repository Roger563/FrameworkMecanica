#include "Mathematics.h"


Mathematics::Mathematics()
{
}

Plane* Mathematics::GetPlane(glm::vec3 point, glm::vec3 normal)
{
    return new Plane(normal, -(point.x * normal.x + point.y * normal.y + point.z * normal.z));
}

Plane* Mathematics::GetPlane(glm::vec3 point, glm::vec3 vec1, glm::vec3 vec2)
{
    return nullptr;
}

void Mathematics::CheckCollisionWithPlane(Plane* plane,ParticleSystem* _ps)
{
    for (int i = 0; i < _ps->GetParticlesCount(); i++)
    {
        if ( ((glm::dot(plane->GetNormal(), _ps->GetParticleLastPosition(i)) + plane->GetD()) *(glm::dot(plane->GetNormal(), _ps->GetParticlePosition(i)) + plane->GetD()) ) <= 0){
            Collide(plane,i,_ps);
        }
    }
}

void Mathematics::Collide(Plane* plane, int index,ParticleSystem* _ps)
{
    _ps->SetParticlePosition(index, _ps->GetParticlePosition(index) - (1 + _ps->GetParticleElasticity()) * (glm::dot(plane->GetNormal(), _ps->GetParticlePosition(index)) + plane->GetD()) * plane->GetNormal());
    _ps->SetVelocity( index,_ps->GetParticleVelocity(index)-(1+_ps->GetParticleElasticity())*(glm::dot(plane->GetNormal(),_ps->GetParticleVelocity(index)))* plane->GetNormal());
}

bool Mathematics::HasCollidedWithSphere(Sphere_intermediate* sphere, glm::vec3 point)
{
    glm::vec3 pc = point - sphere->GetPosition();
    float magnitude = sqrt(pow(pc.x,2) + pow(pc.y,2) + pow(pc.z,2));
    return magnitude < sphere->GetRadius();;
}

void Mathematics::GetSphereCollisionPlane(Sphere_intermediate* sphere, ParticleSystem* _ps)
{
    if (sphere->active) {
        for (int i = 0; i < _ps->GetParticlesCount(); i++)
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

                float result = (-b + sqrt(pow(b, 2) - (double)4.0f * a * c)) / 2.0f;
                float result2 = (-b - sqrt(pow(b, 2) - (double)4.0f * a * c)) / 2.0f;
                float lambda;
                //check lamdas
                if (result < 0) {
                    lambda = result;
                }
                else {
                    lambda = result2;
                }
                //substitute landa on the line equation:
                glm::vec3 intersectionPoint = _ps->GetParticlePosition(i) + lambda * v;

                glm::vec3 planeNormal = Normalize((intersectionPoint - sphere->GetPosition()));
                //collision plane
                Plane* plane = GetPlane(intersectionPoint, planeNormal);
                Collide(plane, i,_ps);
            }
        }
    }
}

glm::vec3 Mathematics::Normalize(glm::vec3 vec)
{
    float magnitude = sqrt(pow(vec.x,2) + pow(vec.y,2) + pow(vec.z,2));
    glm::vec3 normalizedVec = glm::vec3(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude);
    return normalizedVec;
}

void Mathematics::CheckCollisionWithCapsule(glm::vec3 center1, glm::vec3 center2, float radius, ParticleSystem* _ps)
{
    for (int i = 0; i < _ps->GetParticlesCount(); i++) {

        glm::vec3 capsuleCenterVector = center2 - center1;
        glm::vec3 normal = glm::normalize(capsuleCenterVector);
        glm::vec3 particlePos = _ps->GetParticlePosition(i);
        float d = -(particlePos.x * normal.x + particlePos.y * normal.y + particlePos.z * normal.z);
        float lamda = (-d - glm::dot(center1, normal)) / glm::dot(normal, capsuleCenterVector);
        glm::vec3 ClosestPoint = glm::vec3(center1.x + lamda * capsuleCenterVector.x, center1.y + lamda * capsuleCenterVector.y, center1.z + lamda * capsuleCenterVector.z);

        if (glm::length(ClosestPoint-particlePos) < radius) {
            GetCapsuleCollisionPlane(i,center1,center2,radius,_ps);
        }
    }
}

void Mathematics::GetCapsuleCollisionPlane(int id, glm::vec3 center1, glm::vec3 center2, float radius, ParticleSystem* _ps)
{
    glm::vec3 capsuleCenterVector = center2 - center1;
    glm::vec3 normal = glm::normalize(capsuleCenterVector);
    glm::vec3 particlePos = _ps->GetParticlePosition(id);
    float d = -(particlePos.x * normal.x + particlePos.y * normal.y + particlePos.z * normal.z);
    float lamda = (-d - glm::dot(center1, normal)) / glm::dot(normal, capsuleCenterVector);
    glm::vec3 closestPoint = glm::vec3(center1.x + lamda * capsuleCenterVector.x, center1.y + lamda * capsuleCenterVector.y, center1.z + lamda * capsuleCenterVector.z);
    lamda = glm::clamp(lamda, 0.f, 1.f);
    //check if is outside the cylinder
    if (lamda > 0.99f) {
        GetSphereCollisionPlane(new Sphere_intermediate(center2,radius),_ps);
    }
    else if (lamda < 0.01f) {
        GetSphereCollisionPlane(new Sphere_intermediate(center1, radius),_ps);
    }
    else{
        //collision with cilinder
        float length;
        int counter=5;
        glm::vec3 pointInBetween;
        glm::vec3 Pos1 = _ps->GetParticlePosition(id);
        glm::vec3 Pos2 = _ps->GetParticleLastPosition(id);
        do {
            length = glm::length(pointInBetween - closestPoint);
            pointInBetween = ((_ps->GetParticlePosition(id) + _ps->GetParticleLastPosition(id)) / 2.0f);

            if ( length> radius + 0.2) {
                Pos2 = pointInBetween;
            }
            else {
                Pos1 = pointInBetween;
            }
            counter--;
        } while (!glm::abs(length-radius)< 0.2 && counter>0);
        Collide(GetPlane(pointInBetween,(pointInBetween - closestPoint)), id,_ps);
    }
    

    glm::vec3 lastPosCurrentPos = _ps->GetParticlePosition(id) - _ps->GetParticleLastPosition(id);

    
}








