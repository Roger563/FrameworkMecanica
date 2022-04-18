#include "Cape.h"

Cape::Cape()
{
	mesh = new Mesh();
	_verletIntegrator = VerletIntegrator(mesh);
}

void Cape::Update(float dt)
{
	mesh->Update(dt);
	_verletIntegrator.Verlet(dt);
}

void Cape::RenderUpdate()
{
	mesh->RenderUpdate();
}

void Cape::RenderGui()
{
}
