#pragma once
#include "include/Mesh.h"
namespace ClothMesh {
	extern void updateClothMesh(std::vector<glm::vec3> array_data);
	extern const int numCols;
	extern const int numRows;
};
class VerletIntegrator
{
private:
	Mesh* _mesh;
	glm::vec3 _force;

public:
	VerletIntegrator(Mesh* mesh);
	VerletIntegrator();
	

	void Verlet(float dt);
	glm::vec3 CalculateNextPos(int index, float dt);
};

