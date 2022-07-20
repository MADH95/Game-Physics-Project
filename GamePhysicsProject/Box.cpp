/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Box.h"

using namespace std;

void Box::update(float dt)
{
	collider->update(params->transform);
}

void Box::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = params->transform.getPosition();
	vec2 direction = normalize(params->transform.getRightDir());

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	vec2 mainDir = (direction * radii.x * aspectRatio) / (float)width;
	vec2 orthDir = (vec2(-direction.y, direction.x) * radii.y) / (float)height;
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
						       (position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_QUADS);
	glColor3f(colour.r, colour.g, colour.b);
	vec2 vertex = 2.0f * (mainDir + orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (-mainDir + orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (-mainDir - orthDir);
	glVertex2f(vertex.x, vertex.y);
	vertex = 2.0f * (mainDir - orthDir);
	glVertex2f(vertex.x, vertex.y);
	glEnd();

	//collider->draw(width, height);
}