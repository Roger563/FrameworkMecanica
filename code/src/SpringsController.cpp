
#include "..\include\SpringsController.h"

SpringsController::SpringsController(std::vector<spring> structuralSprings, std::vector<spring> bendingSprings, std::vector<spring> shearSprings)
{
	_structuralSprings = structuralSprings;
	_bendingSprings = bendingSprings;
	_shearSPrings = shearSprings;
	
	_structuralSpringsEnabled = true;
	_bendingSpringsEnabled = true;
	_shearSpringsEnabled = true;
}

void SpringsController::UpdateSprings()
{
	if (_structuralSpringsEnabled) {
		for (int i = 0; i < _structuralSprings.size();i++) {
			_structuralSprings[i].UpdateSpring();
		}
	}
	
	if (_bendingSpringsEnabled) {
		for (int i = 0; i < _bendingSprings.size(); i++) {
			_bendingSprings[i].UpdateSpring();
		}
	}

	if (_shearSpringsEnabled) {
		for (int i = 0; i < _shearSPrings.size(); i++) {
			_shearSPrings[i].UpdateSpring();
		}
	}
	
}

void SpringsController::AddStructuralSpring(std::vector<spring> _springs)
{
	_structuralSprings = _springs;
}
