#include "Mesh.h"
Mesh::Mesh() {
	_particleSystem = new ParticleSystem(500,0,1);
	renderCloth = true;
	//set initial pos
	setInitialPos();
	setSprings();
	
}

void Mesh::Update(float dt)
{
	springController->UpdateSprings();
}

void Mesh::setInitialPos()
{
	glm::vec3* positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	for (int row = 0; row < ClothMesh::numRows; row++) {

		for (int col = 0; col < ClothMesh::numCols; col++) {
			int index = col + row * ClothMesh::numCols;
			positions[index] = glm::vec3(row, col, 0.f);
			_particleSystem->SetParticlePosition(index, glm::vec3((float)row/2.0f  -3.25f,4.0f , (float)col / 2.0f + 1));
		}
	}


	for (int row = 0; row < ClothMesh::numRows; row++) {

		for (int col = 0; col < ClothMesh::numCols; col++) {
			int index = col + row * ClothMesh::numCols;
			positions[index] = glm::vec3(row, col, 0.f);
			_particleSystem->SetParticleLastPosition(index, glm::vec3((float)row / 2.0f - 3.25f,4.0f , (float)col / 2.0f + 1));
		}
	}
	_particleSystem->fixParticle(GetIndex(0, 0));
	_particleSystem->fixParticle(GetIndex(0, ClothMesh::numCols-1));
}

void Mesh::setSprings()
{
	
	//Structural
	float structuralRestLength = glm::length((_particleSystem->GetParticlePosition(1) - _particleSystem->GetParticlePosition(2)));
	std::vector<spring> tempStructural;
	std::vector<spring> tempBending;
	std::vector<spring> tempShear;
	for (int row = 0; row < ClothMesh::numRows; row++) {
		for (int col = 0; col < ClothMesh::numCols; col++) {

			if (col < ClothMesh::numCols - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row, col + 1),structuralRestLength,_particleSystem,0.95));
			}

			if (row < ClothMesh::numRows - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row+1, col), structuralRestLength, _particleSystem, 0.95));
			}

		}
	}

	springController = new SpringsController(tempStructural, tempBending, tempShear);
}

void Mesh::RenderUpdate()
{
	ClothMesh::updateClothMesh((_particleSystem->GetPositions()));
}

void Mesh::RenderGui()
{
}

int Mesh::GetIndex(int row, int col)
{
	return col + row * ClothMesh::numCols;
}

Mesh::~Mesh()
{
	renderCloth = false;
}
