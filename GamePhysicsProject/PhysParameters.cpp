/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "PhysParameters.h"
#include "Utils.h"

float PhysParameters::getInverseMass()
{
	return inverseMass;
}

float PhysParameters::getMass()
{
	if (inverseMass == 0.0f)
		return FLT_MAX;
	else
		return 1 / inverseMass;
}

void PhysParameters::setInverseMass(float mass)
{
	if (mass > 0)
		inverseMass = 1 / mass;
	else
		inverseMass = 0.0f;
}

float PhysParameters::getRestitution()
{
	return restitution;
}

void PhysParameters::setRestitution(float restit)
{
	restitution = Utils::clamp(restit);
}

vec2 PhysParameters::getResultant()
{
	return forceAccum;
}

void PhysParameters::clearAccumulator()
{
	forceAccum = vec2(0);
}

void PhysParameters::addForce(const vec2 const &force)
{
	forceAccum += force;
}