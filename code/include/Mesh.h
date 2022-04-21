#pragma once
#include "Simulator.h"
#include <glm\glm.hpp>
#include "../SpringsController.h"
#include "Sphere_intermediate.h"
#include "Mathematics.h"
extern bool renderCloth;
namespace ClothMesh {
	extern void updateClothMesh(std::vector<glm::vec3> array_data);
	extern const int numCols;
	extern const int numRows;
}
extern bool renderSphere;
class Mesh
{
	
	float _timer;
	Mesh* mesh;
	Sphere_intermediate* _sphere;
	Mathematics* mathematics;
	float _kStructural;
	float _kBending;
	float _kShear;

	float _dStructural;
	float _dBending;
	float _dShear;

	float _structuralRestLength;
	float _shearRestLength;
	float _bendingRestLength;
public:
	ParticleSystem* _particleSystem;
	SpringsController* springController;
	Mesh();

	void Reset();
	void Update(float dt);
	void setInitialPos();
	void setSprings(bool structural,bool shear,bool bending);
	void RenderUpdate();
	void RenderGui();
	int GetIndex(int row, int col);
	~Mesh();




};

