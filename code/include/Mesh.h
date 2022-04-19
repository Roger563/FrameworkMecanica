#pragma once
#include "Simulator.h"
#include <glm\glm.hpp>
#include "../SpringsController.h"
extern bool renderCloth;
namespace ClothMesh {
	extern void updateClothMesh(std::vector<glm::vec3> array_data);
	extern const int numCols;
	extern const int numRows;
}
class Mesh
{
	
	
public:
	ParticleSystem* _particleSystem;
	SpringsController* springController;
	Mesh();

	void Update(float dt);
	void setInitialPos();
	void setSprings();
	void RenderUpdate();
	void RenderGui();
	int GetIndex(int row, int col);
	~Mesh();




};

