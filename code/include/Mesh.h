#pragma once
#include "Simulator.h"
#include <glm\glm.hpp>
#include "ParticleSystem.h"
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
	Mesh();

	void Update(float dt);
	void setInitialPos();
	void RenderUpdate();
	void RenderGui();
	int GetIndex(int row, int col);
	~Mesh();




};

