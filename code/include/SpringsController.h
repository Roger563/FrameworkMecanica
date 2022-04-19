#pragma once
#include "../spring.h"
#include <vector>
class SpringsController
{
	std::vector<spring> _structuralSprings;
	std::vector<spring> _bendingSprings;
	std::vector<spring> _shearSPrings;

	bool _structuralSpringsEnabled;
	bool _bendingSpringsEnabled;
	bool _shearSpringsEnabled;

public:
	SpringsController(std::vector<spring> structuralSprings, std::vector<spring> bendingSprings, std::vector<spring> shearSprings);

	void UpdateSprings();

	void AddStructuralSpring(std::vector<spring> _springs);


};

