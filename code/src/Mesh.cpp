#include "Mesh.h"
#include <imgui/imgui.h>
Mesh::Mesh() {
	_particleSystem = new ParticleSystem(500,0.6f,1);
	renderCloth = true;
	mathematics = new Mathematics();
	//set initial pos
	_timer = 0;
	_sphere = new Sphere_intermediate(glm::vec3(0,0,0), 2);
	_kStructural = 5000;
	_kBending= 5000;
	_kShear=5000;

	_dStructural = 20;
	_dBending = 20;
	_dShear = 20;

	_shearRestLength = glm::sqrt(0.5f);
	_structuralRestLength = 0.5f;
	_bendingRestLength = 1;
	setInitialPos();
	setSprings(true,true,true);
	
}

void Mesh::Reset()
{
	setInitialPos();
	bool tempStructural = springController->_structuralSpringsEnabled;
	bool tempShear= springController->_shearSpringsEnabled;
	bool tempBending= springController->_bendingSpringsEnabled;
	setSprings(tempStructural,tempShear,tempBending);
}

void Mesh::Update(float dt)
{
	if (_timer >= 5) {
		Reset();
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

void Mesh::setSprings(bool structural, bool shear, bool bending)
{
	std::vector<spring> tempStructural;
	std::vector<spring> tempBending;
	std::vector<spring> tempShear;
	bool doBendingHorizontal = true;
	bool doBendingVertical = true;
	for (int row = 0; row < ClothMesh::numRows; row++) {
		for (int col = 0; col < ClothMesh::numCols; col++) {

			//Structural
			if (col < ClothMesh::numCols - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row, col + 1),_structuralRestLength,_particleSystem, _kStructural, _dStructural));
			}

			if (row < ClothMesh::numRows - 1) {
				tempStructural.push_back(spring(GetIndex(row, col), GetIndex(row+1, col), _structuralRestLength, _particleSystem, _kStructural, _dStructural));
			}
			
			//Shear
			if (row < ClothMesh::numRows - 1) {
				if (col < ClothMesh::numCols - 1) {
					tempShear.push_back(spring(GetIndex(row, col), GetIndex(row + 1, col + 1), _shearRestLength, _particleSystem, _kShear, _dShear));
				}
				if (col > 0) {
					tempShear.push_back(spring(GetIndex(row, col), GetIndex(row + 1, col - 1), _shearRestLength, _particleSystem, _kShear, _dShear));
				}
			}
			//Bending
			if (row + 2 < ClothMesh::numRows  ) {
					tempBending.push_back(spring(GetIndex(row, col), GetIndex(row + 2, col), _bendingRestLength, _particleSystem, _kBending,_dBending));
			}
			
			if (col + 2 < ClothMesh::numCols ) {
					tempBending.push_back(spring(GetIndex(row, col), GetIndex(row, col + 2), _bendingRestLength, _particleSystem, _kBending,_dBending));

			}
			
		}
	}
	
	delete(springController);
	springController = new SpringsController(tempStructural, tempBending, tempShear, structural,bending,shear);
}

void Mesh::RenderUpdate()
{
	ClothMesh::updateClothMesh((_particleSystem->GetPositions()));
}

void Mesh::RenderGui()
{
	ImGui::Checkbox(
		"structural springs active",
		&springController->_structuralSpringsEnabled
	);
	ImGui::Checkbox(
		"shear springs active",
		&springController->_shearSpringsEnabled
	);
	ImGui::Checkbox(
		"bending springs active",
		&springController->_bendingSpringsEnabled
	);
	if (ImGui::CollapsingHeader("Constants (will change on the next reset) ")) {
		ImGui::SliderFloat(
			"structural spring k",
			&_kStructural, // pointer to an array of 3 floats
			500.0f, // min
			5000.0f // max
		);
		ImGui::SliderFloat(
			"shear spring k",
			&_kShear, // pointer to an array of 3 floats
			500.0f, // min
			5000.0f // max
		);
		ImGui::SliderFloat(
			"bending spring k",
			&_kBending, // pointer to an array of 3 floats
			500.0f, // min
			5000.0f // max
		);

		ImGui::SliderFloat(
			"structural spring dumping",
			&_dStructural, // pointer to an array of 3 floats
			1.0f, // min
			25.0f // max
		);
		ImGui::SliderFloat(
			"shear spring dumping",
			&_dShear, // pointer to an array of 3 floats
			1.0f, // min
			25.0f // max
		);
		ImGui::SliderFloat(
			"bending spring dumping",
			&_dBending, // pointer to an array of 3 floats
			1.0f, // min
			25.0f // max
		);

	}
	if (ImGui::CollapsingHeader("Rest Lengths (will change on the next reset)")) {
		ImGui::SliderFloat(
			"structural spring rest length",
			&_structuralRestLength, // pointer to an array of 3 floats
			0.1f, // min
			2.0f // max
		);
		ImGui::SliderFloat(
			"shear spring rest length",
			&_shearRestLength, // pointer to an array of 3 floats
			0.1f, // min
			2.0f // max
		);
		ImGui::SliderFloat(
			"bending spring rest length",
			&_bendingRestLength, // pointer to an array of 3 floats
			0.1f, // min
			2.0f // max
		);
	}
		
	
}

int Mesh::GetIndex(int row, int col)
{
	return col + row * ClothMesh::numCols;
}

Mesh::~Mesh()
{
	renderCloth = false;
}
