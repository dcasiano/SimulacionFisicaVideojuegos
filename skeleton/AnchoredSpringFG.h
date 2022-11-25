#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG: public SpringForceGenerator
{
public:
	AnchoredSpringFG(double k, double restLength, Vector3 const& anchorPos);
	~AnchoredSpringFG();
};

