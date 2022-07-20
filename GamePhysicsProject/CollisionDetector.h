/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "glm\glm.hpp"
#include "PhysicsEntity.h"
#include "CollisionData.h"

using namespace glm;

class CollisionDetector
{
public:
	CollisionDetector() {}
	virtual ~CollisionDetector() {}
	static	CollisionData* CheckCollision(PhysicsEntity* obj1, PhysicsEntity* obj2);

private:
	static bool SphereSphereCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);

	static bool SphereAABBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);
	static bool AABBAABBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);

	static bool SphereOBBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);
	static bool OBBOBBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);

	static bool SphereSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);
	static bool OBBSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);
	static bool SegmentSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data);
};