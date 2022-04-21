#pragma once
#include "../spring.h"
#include <vector>
class SpringsController
{
	std::vector<spring> _structuralSprings;
	std::vector<spring> _bendingSprings;
	std::vector<spring> _shearSPrings;

	

public:
	bool _structuralSpringsEnabled;
	bool _bendingSpringsEnabled;
	bool _shearSpringsEnabled;

	SpringsController(std::vector<spring> structuralSprings, std::vector<spring> bendingSprings, std::vector<spring> shearSprings,bool sEnabled,bool bEnabled,bool shEnabled);

	void UpdateSprings();

	void AddStructuralSpring(std::vector<spring> _springs);


};

