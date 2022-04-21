#pragma once
#include <glm\glm.hpp>
#include "ParticleSystem.h"
namespace ClothMesh {
	extern void updateClothMesh(std::vector<glm::vec3> array_data);
	extern const int numCols;
	extern const int numRows;
}
class spring
{
	int _particle1Index;
	int _particle2Index;
	float _restLength;
	float _k;
	float _damping;
	glm::vec3 _force;
	ParticleSystem *_particleSystem;
	

public:
	spring(int particle1Index, int particle2Index,float restingLength, ParticleSystem* particleSystem,float k,float damping);
	void UpdateSpring();
};

