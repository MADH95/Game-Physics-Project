/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include <limits>
#include <iostream>

#include "Utils.h"

using namespace std;

// TOLERANCE value
const float Utils::TOLERANCE = 7.0f;

// Constant vectors to define the 4 cardinal directions in 2D
const vec2 Utils::up = vec2(0, 1);
const vec2 Utils::down = vec2(0, -1);
const vec2 Utils::right = vec2(1, 0);
const vec2 Utils::left = vec2(-1, 0);

// Function to Clamp a float between 0 and 1
float Utils::clamp(float val)
{
	return max(min(val, 1.0f), 0.0f);
}

// Function to find the distance between 2 points
float Utils::distanceBetweenPoints(const vec2& point1, const vec2& point2)
{
	return distance(point1, point2);
}

// Find closest point to AABB
vec2 Utils::closestPointOnAABB(const vec2& point, const AABB* box)
{
	vec2 centre = box->getPosition();
	vec2 radii = box->getRadii();
	vec2 normal = Utils::getAABBFaceNormal(point, box);
	float radius = abs(dot(normal, radii));
	vec2 projectedPoint = projectPointOnPlane((point - centre), normal, radius);
	return projectedPoint + centre;
}

// Function to find the distance between a point and a plane
float Utils::disanceBetweenPointAndPlane(const vec2& point, const vec2& normal, float offset)
{
	return abs(dot(point, normal) - offset);
}

// Function to project a point onto a plane 
vec2 Utils::projectPointOnPlane(const vec2& point, const vec2& normal, float offset)
{
	float distance = Utils::disanceBetweenPointAndPlane(point, normal, offset);
	return point - distance * normal;
}

// Find AABB face normal
vec2 Utils::getAABBFaceNormal(const vec2& const point, const AABB* const box)
{
	char mask = Utils::computePointMask(point, box);
	vec2 normal = vec2(0);
	if ((mask & 1) == 1)	// +x
	{
		normal += Utils::right;
	}
	if ((mask & 2) == 2)	// -x
	{
		normal += Utils::left;
	}
	if ((mask & 4) == 4)	// +y
	{
		normal += Utils::up;
	}
	if ((mask & 8) == 8)	// -y
	{
		normal += Utils::down;
	}
	return normalize(normal);
}

/*
Mask is computed as in the following ASCII image.

This is foe the 2D case with codes for +/-x and +/-y

0110	|	+y 0100   	|	0101
-----------------------------------
-x 0010	|	   0000		|	+x 0001
-----------------------------------
1010	|	-y 1000  	|	1001

the 3D case for +/-z is similar but using 6 bits instead of 4

*/
char Utils::computePointMask(const vec2& point, const AABB* box)
{
	vec2 position = box->getPosition();
	vec2 radii = box->getRadii();

	char mask = 0;
	if (pointIsAbovePlane(point, Utils::right, -position.x - radii.x))
	{
		//cout << "X" << endl;
		mask |= 1;// +x
	}
	if (pointIsAbovePlane(point, Utils::left, position.x - radii.x))
	{
		//cout << "-X" << endl;
		mask |= 2;	// -x
	}
	if (pointIsAbovePlane(point, Utils::up, -position.y - radii.y))
	{
		//cout << "Y" << endl;
		mask |= 4;	// +y
	}
	if (pointIsAbovePlane(point, Utils::down, position.y - radii.y))
	{
		//cout << "-Y" << endl;
		mask |= 8;	// -y
	}
	return mask;
}

// Function to check if a point is above a plane
bool Utils::pointIsAbovePlane(const vec2& point, const vec2& normal, float offset)
{
	return dot(point, normal) + offset > FLT_EPSILON;
}

// Find closest point on OBB
vec2 Utils::closestPointOnOBB(const vec2& point, const OBB* const obox)
{
	// Declare OBB Directions
	vector<vec2> dirs{ obox->getDirection(), obox->getOrthogonal() };

	vec2 distVec = point - obox->getPosition(); // Vector between point and center of OBB
	vec2 closestPoint = obox->getPosition(); // Initialise closestPoint to Center of OBB

	//Cycle through each axis
	for (int i = 0; i < 2; i++)
	{
		// Project distVec onto the current direction, then clamp it to the edges off the OBB
		float dist = dot(distVec, dirs[i]);
		if (dist > obox->getRadii()[i] + (1 / TOLERANCE))
			dist = obox->getRadii()[i];

		if (dist < -obox->getRadii()[i] - (1 / TOLERANCE))
			dist = -obox->getRadii()[i];

		// Add the modified dist to closestPoint
		closestPoint += dist * dirs[i];
	}

	//Return closestPoint
	return closestPoint;
}

// Find face normal of OBB
vec2 Utils::getOBBFaceNormal(const vec2& point, const OBB* const obox)
{
	// Initialise normal
	vec2 normal = vec2(0);

	vec2 closestPoint = closestPointOnOBB(point, obox) - obox->getPosition();

	vec2 xDir = obox->getDirection();
	vec2 yDir = obox->getOrthogonal();
	vec2 radii = obox->getRadii();

	float valx = dot(closestPoint, xDir);
	float valy = dot(closestPoint, yDir);

	//normal = -(valx / radii.x * xDir + valy / radii.y * yDir); // Causes stange vector directions

	// Get normal direction based on the distance from the closest point compared to the radii, within a TOLERANCE
	if (abs(valx) <= radii.x + (1/TOLERANCE) && abs(valx) >= radii.x - (1/TOLERANCE))
	{
		if (valx < 0)
			normal -= xDir;
		else if(valx > 0)
			normal += xDir;
	}
	if (abs(valy) <= radii.y + (1/TOLERANCE) && abs(valy) >= radii.y - (1/TOLERANCE))
	{
		if (valy < 0)
			normal -= yDir;
		else if (valy > 0)
		{
			normal += yDir;
		}
	}

	// Return normalized normal
	return normalize(normal);
}

// Find normal of Sphere
vec2 Utils::getSphereNormal(const vec2& point, const BoundingSphere* const sphere)
{
	return normalize(point - sphere->getPosition());
}

// Find closest point to Segment
vec2 Utils::closestPointOnSegment(const vec2& point, const SegmentCollider* const seg)
{
	vec2 v = point - seg->getPosition();
	float dist = dot(v, seg->getDirection());

	// If the given point is past the endpoint of the segment, clamp the point to the endpoint, else if the given point is before the startpoint of the segment, clamp the point to the startpoint
	dist = /*if*/ dist + seg->getLength() < FLT_EPSILON ?
			-seg->getLength() 
	/*else if*/: dist - seg->getLength() > FLT_EPSILON ?
				seg->getLength() : dist;

	// Return the closest point
	return seg->getPosition() + (dist * seg->getDirection());
}

// Find normal of Segment
vec2 Utils::getSegmentNormal(const vec2& point, const SegmentCollider* const seg)
{
	// Initialize normal as an empty vector
	vec2 normal = vec2(0);
	// Find the closest point ot the given point
	vec2 closestPoint = closestPointOnSegment(point, seg);
	// Return the normalized vector between the closest point and the given point
	return normalize(closestPoint - point);
}

// Find orientation of point to segment
char Utils::getOrientation(const vec2& point, const SegmentCollider* const seg)
{
	// Temp variables for start and end of segment
	vec2 start = seg->getStart();
	vec2 end = seg->getEnd();

	// Determine orientation of point to segment
	float val = ((end.y - start.y) * (point.x - end.x)) - ((end.x - start.x) * (point.y - end.y));

	// Point is colinear with segment if val ~= 0
	if (abs(val) <= (TOLERANCE * 200.0f)) return 0;

	// Point is clockwise from segment if val > 0
	// Point is counter-clockwise from segment if val < 0
	return (val > 0) ? 1 : 2;
}

// Find if point is on a segment
bool Utils::pointIsOnSegment(const vec2& point, const SegmentCollider* const seg)
{
	// Temp variables for start and end of line
	vec2 start = seg->getStart();
	vec2 end = seg->getEnd();

	// If point lies on line, return true
	if (point.x <= max(start.x + TOLERANCE, end.x + TOLERANCE) && point.x >= min(start.x - TOLERANCE, end.x - TOLERANCE) &&
		point.y <= max(start.y + TOLERANCE, end.y + TOLERANCE) && point.y >= min(start.y - TOLERANCE, end.y - TOLERANCE))
		return true;
	// Otherwise return false
	return false;
}