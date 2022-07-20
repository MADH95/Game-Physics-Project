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
#include "OBB.h"

using namespace std;
using namespace glm;

class Box : public PhysicsEntity
{
private:
	vec2 radii;
	vec3 colour;

public:
	Box(vec2 radii, PhysParameters* par, vec3 colour) : radii(radii), colour(colour)
	{
		params = par;
		collider = new OBB(radii, params->transform);
	}
	virtual ~Box() {}

	void update(float dt);
	void draw(int width, int height);
};