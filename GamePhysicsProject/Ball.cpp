/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Ball.h"
#include <iostream>

using namespace std;

void Ball::update(float dt)
{
	collider->update(params->transform);
}

void Ball::draw(int width, int height) // coordinates need to be in space (-aspectRatio, aspectRatio)x(-1, 1)
{
	vec2 position = params->transform.getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
							   (position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	// Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(colour.r, colour.g, colour.b);								// Cyan
	glVertex2f(0.0f, 0.0f);										// Center of circle
	int numSegments = 100;
	float angle;
	for (int i = 0; i <= numSegments; i++) {					// Last vertex same as first vertex
		angle = i * 2.0f * pi<float>()/ numSegments;			// 360 deg for all segments
		glVertex2f( cos(angle) * (2.0f * radius / width)* aspectRatio,
			        sin(angle) * (2.0f * radius / height));
	}
	glEnd();
}