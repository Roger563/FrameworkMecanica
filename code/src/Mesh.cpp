#include "Mesh.h"
Mesh::Mesh() {
	_particleSystem = new ParticleSystem(500,0.6f,1);
	renderCloth = true;
	mathematics = new Mathematics();
	//set initial pos
	_timer = 0;
	_sphere = new Sphere_intermediate(glm::vec3(0,0,0), 2);
	setInitialPos();
	setSprings();
}

void Mesh::Update(float dt)
{
	if (_timer >= 20) {
		setInitialPos();
		_timer = 0;
	}
	for (int row = 0; row < ClothMesh::numRows; row++) {
		for (int col = 0; col < ClothMesh::numCols; col++) {
			//reset acceleration
			_particleSystem->SetAcceleration(GetIndex(row, col), glm::vec3(0, 0, 0));
			//add gravity
			_particleSystem->SetAcceleration(GetIndex(row, col), glm::vec3(0, -9.8, 0));

		}
	}
	//COLLISIONS
	//WALLS
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 1, 0), 0.f),_particleSystem); // DOWN
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, -1, 0), 10.f), _particleSystem); // UP
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(1, 0, 0), 5.f), _particleSystem); // X NEGATIVE
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(-1, 0, 0), 5.f), _particleSystem); // X POSITIVE
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, 1), 5.f), _particleSystem); // Z NEGATIVE
	mathematics->CheckCollisionWithPlane(new Plane(glm::vec3(0, 0, -1), 5.f), _particleSystem); // Z POSITIVE
	//SPHERE
	mathematics->GetSphereCollisionPlane(_sphere, _particleSystem);


	springController->UpdateSprings();
	_timer += dt;
}

void Mesh::setInitialPos()
{
	delete(_sphere);
	//el random en Y el capem perque no aparegui dins la tela
	_sphere = new Sphere_intermediate(glm::vec3(-5 + rand() %11, 1+ rand() %7, -5 + rand() % 11), 2);
	glm::vec3* positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	for (int row = 0; row < ClothMesh::numRows; row++) {

		for (int col = 0; col < ClothMesh::numCols; col++) {
			int index = col + row * ClothMesh::numCols;
			positions[index] = glm::vec3(row, col, 0.f);
			_particleSystem->SetParticlePosition(index, glm::vec3((float)row/2 -5  ,9.9 , (float)col / 2.0f - 4.25));
			_particleSystem->SetParticleLastPosition(index, glm::vec3((float)row/2 -5 ,9.9, (float)col / 2.0f - 4.25));
			_particleSystem->SetVelocity(index, glm::vec3(0, 0, 0));
			_particleSystem->SetAcceleration(index, glm::vec3(0,-9.8,0));
		}
	}



	_particleSystem->fixParticle(GetIndex(0, 0));
	_particleSystem->fixParticle(GetIndex(0, ClothMesh::numCols-1));
}

void Mesh::setSprings()
{
	std::vector<spring> tempStructural;
	std::vector<spring> tempBending;
	std::vector<spring> tempShear;
	float k = 800;
	bool doBendingHorizontal = true;
	bool doBendingVertical = true;
	float structuralRestLength = glm::length((_particleSystem->GetParticlePosition(GetIndex(0, 0)) - _particleSystem->GetParticlePosition(GetIndex(0, 1))));
	float ShearRestLength = glm::length((_particleSystem->GetParticlePosition(GetIndex(0,0)) - _particleSystem->GetParticlePosition(GetIndex(1,1))));
	float bendingRestLength = glm::length((_particleSystem->GetParticlePosition(GetIndex(0, 0)) - _particleSystem->GetParticlePosition(GetIndex(0, 2))));
	for (int row = 0; row < ClothMesh::numRows; row++) {
		for (int col = 0; col < ClothMesh::numCols; col++) {

			//Structural
			if (col < ClothMesh::numCols - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row, col + 1),structuralRestLength,_particleSystem,k));
			}

			if (row < ClothMesh::numRows - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row+1, col), structuralRestLength, _particleSystem,k));
			}
			
			//Shear
			if (row < ClothMesh::numRows - 1) {
				if (col < ClothMesh::numCols - 1) {
					tempShear.push_back(spring(GetIndex(row, col), GetIndex(row + 1, col + 1), ShearRestLength, _particleSystem, k));
				}
				if (col > 0) {
					tempShear.push_back(spring(GetIndex(row, col), GetIndex(row + 1, col - 1), ShearRestLength, _particleSystem, k));
				}
			}
			//Bending
			if (row + 2 < ClothMesh::numRows  ) {
					tempBending.push_back(spring(GetIndex(row, col), GetIndex(row + 2, col), bendingRestLength, _particleSystem, k));
			}
			
			if (col + 2 < ClothMesh::numCols ) {
					tempBending.push_back(spring(GetIndex(row, col), GetIndex(row, col + 2), bendingRestLength, _particleSystem, k));

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
