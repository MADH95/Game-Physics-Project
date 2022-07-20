/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>

#include "PhysicsEntity.h"
#include "BoundingSphere.h"

using namespace std;
using namespace glm;

class Ball : public PhysicsEntity
{
private:
	float radius;
	vec3 colour;

public:
	Ball(float radius, PhysParameters* par, vec3 colour) :radius(radius), colour(colour)
	{
		params = par; 
		collider = new BoundingSphere(radius, params->transform);
	}

	virtual ~Ball() {}

	void update(float dt);
	
	void draw(int width, int height);
};