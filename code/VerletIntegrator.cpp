#include "VerletIntegrator.h"

VerletIntegrator::VerletIntegrator(Mesh* mesh)
{
	_mesh = mesh;
	_force = glm::vec3(0, -9.8, 0);
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
			_mesh->_particleSystem->SetParticlePosition(_mesh->GetIndex(i, j), CalculateNextPos(_mesh->GetIndex(i, j), dt) );
			
		}
	}
}

glm::vec3 VerletIntegrator::CalculateNextPos(int index,float dt)
{
	glm::vec3 currentPos = _mesh->_particleSystem->GetParticlePosition(index);
	glm::vec3 lastPos = _mesh->_particleSystem->GetParticleLastPosition(index);
	float mass = _mesh->_particleSystem->GetMass();
	glm::vec3 forces = mass * _force;
	_mesh->_particleSystem->SetParticleLastPosition(index, currentPos);
	return ( currentPos + (currentPos - lastPos) + (forces/mass) * (dt*dt) );
	

}
