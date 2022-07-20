/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "AABB.h"

void AABB::update(Transform& trans)
{
	pos = trans.getPosition();
	transform = trans;
}

void AABB::draw(int height, int width)
{
}

const vec2 AABB::getPosition() const
{
	return pos;
}

const vec2 AABB::getRadii() const
{
	return radii;
}