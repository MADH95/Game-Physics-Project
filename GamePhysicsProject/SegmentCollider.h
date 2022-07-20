/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "Collider.h"

using namespace glm;

class SegmentCollider : public Collider
{
private:
	vec2 pos;
	vec2 dir;
	float halfLength;
	Transform transform;

public:
	SegmentCollider(float halfLength, Transform& trans) : halfLength(halfLength), transform(trans)
	{
		dir = normalize(trans.getRightDir());
		pos = trans.getPosition();
	};
	virtual ~SegmentCollider() {};

	void update(Transform& trans);
	void draw(int width, int height);

	const vec2 getPosition() const;
	const vec2 getStart() const;
	const vec2 getEnd() const;
	const float getLength() const;
	const vec2 getDirection() const;
	const vec2 getOrthogonal() const;
};