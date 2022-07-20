/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "SegmentCollider.h"

void SegmentCollider::update(Transform& trans)
{
	dir = normalize(trans.getRightDir());
	pos = trans.getPosition();
	transform = trans;
}

void SegmentCollider::draw(int width, int height)
{
	float halfWidth = 0.5f * width;
	float halfHeight = 0.5f * height;
	float aspectRatio = (width / (float)height);
	vec2 position = transform.getPosition();
	vec2 segmentDirection = normalize(transform.getRightDir()) * halfLength;

	glLoadIdentity();
	glLineWidth(1);
	glBegin(GL_LINES); // This comand draws segments not lines
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(((position.x - segmentDirection.x) / halfWidth - 1.0f) * aspectRatio, (position.y - segmentDirection.y) / halfHeight - 1.0f); // Starting point of the GL_LINES
	glVertex2f(((position.x + segmentDirection.x) / halfWidth - 1.0f) * aspectRatio, (position.y + segmentDirection.y) / halfHeight - 1.0f); // Ending point of the GL_LINES
	glEnd();
}

const vec2 SegmentCollider::getPosition() const
{
	return pos;
}

const vec2 SegmentCollider::getStart() const
{
	return pos - dir * halfLength;
}

const vec2 SegmentCollider::getEnd() const
{
	return pos + dir * halfLength;
}

const float SegmentCollider::getLength() const
{
	return halfLength;
}

const vec2 SegmentCollider::getDirection() const
{
	return dir;
}

const vec2 SegmentCollider::getOrthogonal() const
{
	return vec2(-dir.y, dir.x);
}