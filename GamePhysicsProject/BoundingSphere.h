/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "Collider.h"

using namespace glm;

class BoundingSphere :public Collider
{
private:
	vec2 pos;
	float radius;
	Transform transform;

public:
	BoundingSphere(float radius,Transform& trans) : radius(radius), transform(trans) 
	{
		pos = trans.getPosition();
	}
	virtual ~BoundingSphere() {}

	void update(Transform& trans);
	void draw(int width, int height);

	const vec2 getPosition() const;
	const float getRadius() const;
};
