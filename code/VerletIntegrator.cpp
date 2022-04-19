#include "VerletIntegrator.h"

VerletIntegrator::VerletIntegrator(Mesh* mesh)
{
	_mesh = mesh;
	_force = glm::vec3(0, -9.8, 0);

	for (int i = 0; i < ClothMesh::numRows; i++) {
		for (int j = 0; j < ClothMesh::numCols; j++) {
			_mesh->_particleSystem->SetAcceleration(_mesh->GetIndex(i, j), _force);
		}
	}
}

VerletIntegrator::VerletIntegrator()
{
	_force = glm::vec3(0, -9.8, 0);
}

void VerletIntegrator::Verlet(float dt)
{
	for (int i = 0; i < ClothMesh::numRows; i++) {
		for (int j = 0; j < ClothMesh::numCols; j++) {
			//update position
			int index = _mesh->GetIndex(i, j);
			if (!(_mesh->_particleSystem->isStatic(index))) {
				_mesh->_particleSystem->SetParticlePosition(index, CalculateNextPos(index, dt));
				_mesh->_particleSystem->AddVelocity(index, CalculateVelocity(index, dt));
			}


		}
	}
}

glm::vec3 VerletIntegrator::CalculateNextPos(int index,float dt)
{
	glm::vec3 currentPos = _mesh->_particleSystem->GetParticlePosition(index);
	glm::vec3 lastPos = _mesh->_particleSystem->GetParticleLastPosition(index);
	float mass = _mesh->_particleSystem->GetMass();
	glm::vec3 forces = mass * _mesh->_particleSystem->GetParticleAcceleration(index);
	_mesh->_particleSystem->SetParticleLastPosition(index, currentPos);
	return ( currentPos + (currentPos - lastPos) + (forces/mass) * (dt*dt) );
}

glm::vec3 VerletIntegrator::CalculateVelocity(int index, float dt)
{
	glm::vec3 nextPos = CalculateNextPos(index, dt);
	glm::vec3 currentPos = _mesh->_particleSystem->GetParticlePosition(index);
	return ( (nextPos - currentPos) / dt);
}
