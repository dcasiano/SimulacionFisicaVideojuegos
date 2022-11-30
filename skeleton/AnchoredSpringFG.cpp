#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double restLength, Vector3 const& anchorPos):SpringForceGenerator(nullptr,k,restLength)
{
	other = new Particle(anchorPos, { 0,0,0 }, { 0,0,0 }, 0.0f, { 1,0,0,1 });
	other->setInverseMass(0);
	other->setAsCube();
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other;
}
