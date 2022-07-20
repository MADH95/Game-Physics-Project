/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Transform.h"
// The assumption for this class is that we are not attaching the game object to any hierachy so the coordinates are always expressed directly in world coordinates
Transform::Transform()
{
	// The first column of the transformation matrix matches the direction of the local x axis of the object expressed with respect to the world reference system in homogeneous coords
	// The second column of the transformation matrix matches the direction of the local y axis of the object expressed with respect to the world reference system in homogeneous coords
	// The third column of the transformation matrix contains the position of the object expressed with respect to the world reference system in homogeneous coords
	transformMatrix = mat3(1.0f, 0.0f, 0.0f, 
						   0.0f, 1.0f, 0.0f, 
						   0.0f, 0.0f, 1.0f); //Identity matrix
											  //inputs are done column in rows
											  // i.e. the matrix is transposed
}

// Translate the object by creating a Translation matrix and 
// multiplying it to the transform matrix
void Transform::Translate(vec2 const& translation)
{
	mat3 translationMatrix = mat3(1.0f, 0.0f, 0,
								  0.0f, 1.0f, 0,
		translation.x, translation.y, 1);//<-- This last row is usually omitted in optimised code
													//	  because it is always constant (they use 2x3 matrices), 
													//    but as this code is didactic I left it here to help 
													//	  you match the code with the theory in the lectures

	transformMatrix = translationMatrix * transformMatrix;
}

// Translate the object by creating a Scaling matrix and 
// multiplying it to the transform matrix
void Transform::Scale(vec2 const& scaling)
{
	mat3 scalingMatrix = mat3(scaling.x, 0.0f, 0.0f, 
							  0.0f, scaling.y, 0.0f, 
							  0.0f, 0.0f, 1.0f); //<-- Row omitted in optimised code

	transformMatrix = scalingMatrix * transformMatrix;
}

// Translate the object by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::Rotate(float angle)
{
	float rads = radians(angle);
	float cosx = abs(cos(rads)) < FLT_EPSILON ? 0.0f : 
				cos(rads) + 1 <  FLT_EPSILON ? -1.0f :
				cos(rads) - 1 > -FLT_EPSILON ?  1.0f : cos(rads);
	float sinx = abs(sin(rads)) < FLT_EPSILON ? 0.0f :
				sin(rads) + 1 <  FLT_EPSILON ? -1.0f :
				sin(rads) - 1 > -FLT_EPSILON ?  1.0f : sin(rads);

	mat3 rotateMatrix = mat3(cosx,sinx, 0.0f, 
							 -sinx, cosx, 0.0f,
							 0.0f, 0.0f, 1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}

vec2 Transform::getPosition()
{
	return column(transformMatrix, 2); // The third column of the transformation matrix contains the position of the object in homogeneous coords
}

vec2 Transform::getScale()
{
	float sx = length(column(transformMatrix, 0)); // It measures the length of the local x axis
	float sy = length(column(transformMatrix, 1)); // It measures the length of the local y axis
	return vec2(sx, sy);
}

vec2 Transform::getOrientation()
{

	vec3 col0 = normalize(column(transformMatrix, 0)); // By normalising the x axis whe get the cosine (in the first component of the vector)
												       // and sine (in the second component of the vector) of the angle by which the object is rotated
	return vec2(col0.x, col0.y);
}

// This gives the y axis of the object expressed in world coordinates
vec2 Transform::getUpDir()
{
	vec3 col1 = column(transformMatrix, 1);
	return vec2(col1.x, col1.y); // y Axis
}

// This gives the x axis of the object expressed in world coordinates
vec2 Transform::getRightDir()
{
	vec3 col0 = column(transformMatrix, 0);
	return vec2(col0.x, col0.y); // x Axis
}

mat3 Transform::localToWorldMatrix()
{
	return transformMatrix; //This matrix transforms local coordinates into world coordinates (if we are not using any hierarchical data structure)
}

mat3 Transform::worldToLocalMatrix()
{
	return inverse(transformMatrix);
}