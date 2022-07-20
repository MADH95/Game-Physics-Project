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
#include "SegmentCollider.h"

using namespace std;
using namespace glm;

class Segment : public PhysicsEntity
{
private:
	float halfLength;
	vec3 colour;

public:
	Segment(float halfLength, PhysParameters* par, vec3 colour) : halfLength(halfLength), colour(colour)
	{
		params = par;
		collider = new SegmentCollider(halfLength, params->transform);
	}
	virtual ~Segment() {}

	void update(float dt);
	void draw(int width, int height);
};