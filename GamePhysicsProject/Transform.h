/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm\glm.hpp>
#include<glm\gtc\matrix_access.hpp>

using namespace glm;

class Transform
{
private:
	mat3 transformMatrix;
	
public:
	Transform();
	virtual ~Transform() {}

	void Translate(vec2 const& translation);
	void Scale(vec2 const& scaling);
	void Rotate(float angle);

	vec2 getPosition();
	vec2 getScale();
	vec2 getOrientation();
	vec2 getUpDir();
	vec2 getRightDir();

	mat3 localToWorldMatrix();
	mat3 worldToLocalMatrix();
};