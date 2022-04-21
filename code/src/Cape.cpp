#include "Cape.h"

Cape::Cape()
{
	mesh = new Mesh();
	_verletIntegrator = VerletIntegrator(mesh);
	_step = 5;
	
	renderSphere = true;
}

Cape::~Cape()
{
	delete mesh;
	renderSphere = false;
}

void Cape::Update(float dt)
{
	//reset acceleration
	
	for (int i = 0; i < _step; i++) {

		mesh->Update(dt / _step);
		_verletIntegrator.Verlet(dt / _step);
	}
	
	
}

void Cape::RenderUpdate()
{
	mesh->RenderUpdate();
}

void Cape::RenderGui()
{
	mesh->RenderGui();
}
