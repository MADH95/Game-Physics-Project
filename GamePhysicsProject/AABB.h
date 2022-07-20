/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "Collider.h"

using namespace glm;

class AABB :public Collider
{
private:
	vec2 pos;
	vec2 radii;
	Transform transform;

public:
	AABB(vec2 radii, Transform& trans) : radii(radii), transform(trans) 
	{
		pos = trans.getPosition();
	};
	virtual ~AABB() {};

	void update(Transform& trans);
	void draw(int height, int width);

	const vec2 getPosition() const;
	const vec2 getRadii() const;
};
