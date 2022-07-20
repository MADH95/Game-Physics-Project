/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Segment.h"

using namespace std;

void Segment::update(float dt)
{
	collider->update(params->transform);
}

void Segment::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	float halfWidth = 0.5f * width;
	float halfHeight = 0.5f * height;
	float aspectRatio = (width / (float)height);
	vec2 position = params->transform.getPosition();
	vec2 segmentDirection = normalize(params->transform.getRightDir()) * halfLength;

	glLoadIdentity();
	glLineWidth(1);
	glBegin(GL_LINES); // This comand draws segments not lines
	glColor3f(colour.r, colour.g, colour.b);
	glVertex2f(((position.x - segmentDirection.x) / halfWidth - 1.0f) * aspectRatio, (position.y - segmentDirection.y) / halfHeight - 1.0f); // Starting point of the GL_LINES
	glVertex2f(((position.x + segmentDirection.x) / halfWidth - 1.0f) * aspectRatio, (position.y + segmentDirection.y) / halfHeight - 1.0f); // Ending point of the GL_LINES
	glEnd();

	//collider->draw(width, height);
}