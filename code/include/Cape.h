#pragma once
#include "../include/Simulator.h";
#include "../include/Mesh.h";
#include "../VerletIntegrator.h"
extern bool renderCloth;
namespace ClothMesh {
	extern void updateClothMesh(float* array_data);
	extern const int numCols;
	extern const int numRows;
}
class Cape : public Simulator
{
	Mesh* mesh;
	VerletIntegrator _verletIntegrator;
public:
	Cape();
	void Update(float dt);
	void RenderUpdate();
	void RenderGui();
};

