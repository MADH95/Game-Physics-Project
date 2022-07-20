/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <glm\glm.hpp>

#include "SegmentCollider.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include "OBB.h"

using namespace glm;

class Utils
{
public:
	static const float TOLERANCE;
	static const vec2 up;
	static const vec2 down;
	static const vec2 left;
	static const vec2 right;

	static float clamp(float value);
	static float distanceBetweenPoints(const vec2& point1, const vec2& point2);
	
	static vec2 closestPointOnAABB(const vec2& point, const AABB* const box);
	static vec2 projectPointOnPlane(const vec2& point, const vec2& normal, float offset);
	static float disanceBetweenPointAndPlane(const vec2& point, const vec2& normal, float offset);

	static vec2 getAABBFaceNormal(const vec2& point, const AABB* const box);
	static char computePointMask(const vec2& point, const AABB* const box);
	static bool pointIsAbovePlane(const vec2& point, const vec2& normal, float offset);

	static vec2 closestPointOnOBB(const vec2& point, const OBB* const box);
	static vec2 getOBBFaceNormal(const vec2& point, const OBB* const obox);

	static vec2 getSphereNormal(const vec2& point, const BoundingSphere* const sphere);

	static vec2 closestPointOnSegment(const vec2& point, const SegmentCollider* const seg);
	static vec2 getSegmentNormal(const vec2& point, const SegmentCollider* const seg);

	static char getOrientation(const vec2& point, const SegmentCollider* const seg);
	static bool pointIsOnSegment(const vec2& point, const SegmentCollider* const seg);

private:
	Utils() {}
};