/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once

#include <glm\glm.hpp>
#include <glm\glm.hpp>
#include<glm\gtc\matrix_access.hpp>

#include "Transform.h"

class PhysParameters
{
private:
	float inverseMass;
	float restitution;
	vec2 forceAccum;

public:
	vec2 velocity;
	vec2 acceleration;
	Transform transform;

	PhysParameters(float mass, vec2 pos, vec2 vel, float restit, float angle = 0) : velocity(vel), restitution(restit), forceAccum(vec2(0)), acceleration(vec2(0)), inverseMass(INFINITY)
	{
		setInverseMass(mass);
		transform.Rotate(angle);
		transform.Translate(pos);
	}

	virtual ~PhysParameters() {}

	void setInverseMass(float mass);
	float getInverseMass();
	float getMass();

	void setRestitution(float restit);
	float getRestitution();

	vec2 getResultant();
	void clearAccumulator();
	void addForce(const vec2 const &force);
};