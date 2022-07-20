/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "CollisionDetector.h"
#include "Utils.h"

#include "SegmentCollider.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include "OBB.h"

#include <vector>
#include <iostream>

using namespace std;

CollisionData* CollisionDetector::CheckCollision(PhysicsEntity* obj1, PhysicsEntity* obj2)
{
	CollisionData* data = nullptr;

	// Collision detection between two Spheres
	if (dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr)
		CollisionDetector::SphereSphereCollision(obj1, obj2, &data);

	// Collision detection between Sphere and AABB
	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr) ||
		(dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr))
		CollisionDetector::SphereAABBCollision(obj1, obj2, &data);

	// Collision detection between two AABBs
	if (dynamic_cast<AABB*>(obj1->getCollider()) != nullptr && dynamic_cast<AABB*>(obj2->getCollider()) != nullptr)
		CollisionDetector::AABBAABBCollision(obj1, obj2, &data);

	// Collision detection between Sphere and OBB
	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<OBB*>(obj2->getCollider()) != nullptr) ||
		(dynamic_cast<OBB*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr))
		CollisionDetector::SphereOBBCollision(obj1, obj2, &data);

	// Collision detection between two OBBs
	if (dynamic_cast<OBB*>(obj1->getCollider()) != nullptr && dynamic_cast<OBB*>(obj2->getCollider()) != nullptr)
		CollisionDetector::OBBOBBCollision(obj1, obj2, &data);

	// Collision detection between Sphere and Segment
	if ((dynamic_cast<BoundingSphere*>(obj1->getCollider()) != nullptr && dynamic_cast<SegmentCollider*>(obj2->getCollider()) != nullptr ||
		(dynamic_cast<SegmentCollider*>(obj1->getCollider()) != nullptr && dynamic_cast<BoundingSphere*>(obj2->getCollider()) != nullptr)))
		CollisionDetector::SphereSegmentCollision(obj1, obj2, &data);

	// Collision detection between OBB and Segment
	if ((dynamic_cast<OBB*>(obj1->getCollider()) != nullptr && dynamic_cast<SegmentCollider*>(obj2->getCollider()) != nullptr ||
		(dynamic_cast<SegmentCollider*>(obj1->getCollider()) != nullptr && dynamic_cast<OBB*>(obj2->getCollider()) != nullptr)))
		CollisionDetector::OBBSegmentCollision(obj1, obj2, &data);

	// Collision detection between two Segments
	if (dynamic_cast<SegmentCollider*>(obj1->getCollider()) != nullptr && dynamic_cast<SegmentCollider*>(obj2->getCollider()) != nullptr)
		CollisionDetector::SegmentSegmentCollision(obj1, obj2, &data);

	return data; // Return collision data
}

// Collision Detection between two Spheres
bool CollisionDetector::SphereSphereCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	BoundingSphere* s1 = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	BoundingSphere* s2 = dynamic_cast<BoundingSphere*>(obj2->getCollider());

	// Check if distance between centers is less than the sum of the radii
	float dist = Utils::distanceBetweenPoints(s1->getPosition(), s2->getPosition());
	float penetration = dist - (s1->getRadius() + s2->getRadius());
	bool collision = penetration <= 0;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		(*data)->contact[0].setContactNormal(normalize(obj1->getParams()->transform.getPosition() - obj2->getParams()->transform.getPosition()));
		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collision Detection between Sphere and AABB
bool CollisionDetector::SphereAABBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	AABB* box;
	BoundingSphere* sphere = dynamic_cast<BoundingSphere*>(obj1->getCollider());
	if (sphere != nullptr)
		box = dynamic_cast<AABB*>(obj2->getCollider());
	else
	{
		box = dynamic_cast<AABB*>(obj1->getCollider());
		sphere = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	}

	// Find closes point on AABB, then check if distance between that point and the centre of the sphere is less than the sphere's radius
	vec2 pointOnAABB = Utils::closestPointOnAABB(sphere->getPosition(), box);
	float dist = Utils::distanceBetweenPoints(sphere->getPosition(), pointOnAABB);
	float penetration = dist - sphere->getRadius();
	bool collision = penetration <= 0;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = -Utils::getAABBFaceNormal(sphere->getPosition(), box);
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = Utils::getAABBFaceNormal(sphere->getPosition(), box);
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);
		
		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collisoin Detection between two AABBs
bool CollisionDetector::AABBAABBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	AABB* box1 = dynamic_cast<AABB*>(obj1->getCollider());
	AABB* box2 = dynamic_cast<AABB*>(obj2->getCollider());

	// Check if the distance between centers on the x-axis is less than the sum of the x radii
	vec2 box1ProjCenterX = box1->getPosition().x * Utils::right;
	vec2 box2ProjCenterX = box2->getPosition().x * Utils::right;
	float distX = Utils::distanceBetweenPoints(box1ProjCenterX, box2ProjCenterX);
	float penetrationX = distX - (box1->getRadii().x + box2->getRadii().x);
	bool collisionX = penetrationX <= 0;

	// Check if the distance between centers on the y-axis is less than the sum of the y radii
	vec2 box1ProjCenterY = box1->getPosition().y * Utils::up;
	vec2 box2ProjCenterY = box2->getPosition().y * Utils::up;
	float distY = Utils::distanceBetweenPoints(box1ProjCenterY, box2ProjCenterY);
	float penetrationY = distY - (box1->getRadii().y + box2->getRadii().y);
	bool collisionY = penetrationY <= 0;

	bool collision = collisionX && collisionY;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = -Utils::getAABBFaceNormal(box1->getPosition(), box2);
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = Utils::getAABBFaceNormal(box2->getPosition(), box1);
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		vec2 penetrations = vec2(penetrationX, penetrationY);
		float penetration = dot(penetrations, abs(normal));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collision Detection between Sphere and OBB
bool CollisionDetector::SphereOBBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	bool flipped = false;
	// Get colliders
	OBB* obox;
	BoundingSphere* sphere = dynamic_cast<BoundingSphere*>(obj1->getCollider());

	if (sphere != nullptr)
		obox = dynamic_cast<OBB*>(obj2->getCollider());
	else
	{
		flipped = true;
		obox = dynamic_cast<OBB*>(obj1->getCollider());
		sphere = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	}

	// Find the closest point on OBB, then check if the distance between that point and the center of the sphere is less than the sphere's radius
	vec2 pointOnOBB = Utils::closestPointOnOBB(sphere->getPosition(), obox);
	float dist = Utils::distanceBetweenPoints(sphere->getPosition(), pointOnOBB);
	float penetration = dist - sphere->getRadius();
	bool collision = penetration <= FLT_EPSILON;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = -Utils::getOBBFaceNormal(sphere->getPosition(), obox);
		if (flipped)
		{
			normal = -normal;
		}
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = -normal;
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collision Detection between two OBBs
bool CollisionDetector::OBBOBBCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	OBB* obox1 = dynamic_cast<OBB*>(obj1->getCollider());
	OBB* obox2 = dynamic_cast<OBB*>(obj2->getCollider());
	bool collision = true; // Initialize collision to true

	// Project the vector between the centre of the 2 OBBs onto the current direction, then compare it to the radii of the OBBs projected onto the current direciton to determine seperating axis
	vector<vec2> dirs = { obox1->getDirection(), obox1->getOrthogonal(), obox2->getDirection(), obox2->getOrthogonal() };
	vec2 T = obox1->getPosition() - obox2->getPosition();

	for (auto dirptr = dirs.begin(); dirptr < dirs.end(); dirptr++)
	{
		if (abs(dot(T, *dirptr)) > abs(obox1->getRadii().x * dot(obox1->getDirection(), *dirptr))
			+ abs(obox1->getRadii().y * dot(obox1->getOrthogonal(), *dirptr))
			+ abs(obox2->getRadii().x * dot(obox2->getDirection(), *dirptr))
			+ abs(obox2->getRadii().y * dot(obox2->getOrthogonal(), *dirptr)))
		{
			collision = false;
			break;
		}
	}

	// Check if collision occurred
	if (collision)
	{
		// Fill collision Data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = Utils::getOBBFaceNormal(obox2->getPosition(), obox1);
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = -normal;
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		// Calculate penetration by projecting the vector between OBB centres onto the normal, then subtracting the radii projected onto the normal
		float centreDist = abs(dot(T, normal));
		float radiiDist = abs(obox1->getRadii().x * dot(obox1->getDirection(), normal))
			+ abs(obox1->getRadii().y * dot(obox1->getOrthogonal(), normal))
			+ abs(obox2->getRadii().x * dot(obox2->getDirection(), normal))
			+ abs(obox2->getRadii().y * dot(obox2->getOrthogonal(), normal));
		float penetration = centreDist - radiiDist;

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collision Detection between Sphere and Segment
bool CollisionDetector::SphereSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	SegmentCollider* seg;
	BoundingSphere* sphere = dynamic_cast<BoundingSphere*>(obj1->getCollider());

	if (sphere != nullptr)
		seg = dynamic_cast<SegmentCollider*>(obj2->getCollider());
	else
	{
		seg = dynamic_cast<SegmentCollider*>(obj1->getCollider());
		sphere = dynamic_cast<BoundingSphere*>(obj2->getCollider());
	}

	// Find distance between centre of circle and Segment
	vec2 closestPoint = Utils::closestPointOnSegment(sphere->getPosition(), seg);
	float distance = Utils::distanceBetweenPoints(closestPoint, sphere->getPosition());
	float penetration = distance - sphere->getRadius();
	bool collision = penetration <= 0 ? true : false;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = -Utils::getSphereNormal(closestPoint, sphere);
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = -normal;
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	// Return if collision occurred
	return collision;
}

// Collision Detection between OBB and Segment
bool CollisionDetector::OBBSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	OBB* obox;
	SegmentCollider* seg = dynamic_cast<SegmentCollider*>(obj1->getCollider());

	if (seg != nullptr)
		obox = dynamic_cast<OBB*>(obj2->getCollider());
	else
	{
		obox = dynamic_cast<OBB*>(obj1->getCollider());
		seg = dynamic_cast<SegmentCollider*>(obj2->getCollider());
	}
	bool collision = true; // Initialize collision to true

	// Find the closest point on the segment, then use that to find the seperating direction, then compare the distance between the the centre of the OBB and the closest point on the segment along that direction to the 
	vec2 closestPointSeg = Utils::closestPointOnSegment(obox->getPosition(), seg);
	vec2 seperatingDir = normalize(obox->getPosition() - closestPointSeg);
	vec2 T = obox->getPosition() - closestPointSeg;
	if(abs(dot(T, seperatingDir)) > abs(obox->getRadii().x * dot(obox->getDirection(), seperatingDir))
		+ abs(obox->getRadii().y * dot(obox->getOrthogonal(), seperatingDir)))
		collision = false;

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal = -Utils::getSegmentNormal(obox->getPosition(), seg);
		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = Utils::getSegmentNormal(obox->getPosition(), seg);
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		float distCentre = abs(dot(T, normal));
		float distRadii = abs(obox->getRadii().x * dot(obox->getDirection(), normal))
			+ abs(obox->getRadii().y * dot(obox->getOrthogonal(), normal));
		float penetration = distCentre - distRadii;

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}

// Collision Detection between two Segments
bool CollisionDetector::SegmentSegmentCollision(PhysicsEntity* obj1, PhysicsEntity* obj2, CollisionData** data)
{
	// Get colliders
	SegmentCollider* seg1 = dynamic_cast<SegmentCollider*>(obj1->getCollider());
	SegmentCollider* seg2 = dynamic_cast<SegmentCollider*>(obj2->getCollider());

	// Initialise collision to false
	bool collision = false;

	// Find the four orientations needed to determine collision
	char orient1 = Utils::getOrientation(seg2->getStart(), seg1);
	char orient2 = Utils::getOrientation(seg2->getEnd(), seg1);
	char orient3 = Utils::getOrientation(seg1->getStart(), seg2);
	char orient4 = Utils::getOrientation(seg1->getEnd(), seg2);

	// Check if the orientations match per segment
	if (orient1 != orient2 && orient3 != orient4)
		collision = true;
	else {
		// Check special cases
		// Start point of seg2 lies on the seg1
		if (orient1 == 0 && Utils::pointIsOnSegment(seg2->getStart(), seg1)) collision = true;
		// End point of seg2 is colinear with seg1 and lies on the segment
		if (orient2 == 0 && Utils::pointIsOnSegment(seg2->getEnd(), seg1)) collision = true;
		// Start point of seg1 is colinear with seg2 and lies on the segment
		if (orient3 == 0 && Utils::pointIsOnSegment(seg1->getStart(), seg2)) collision = true;
		// End point of seg1 is colinear with seg2 and lies on the segment
		if (orient4 == 0 && Utils::pointIsOnSegment(seg1->getEnd(), seg2)) collision = true;
	}

	// Check if collision occurred
	if (collision)
	{
		// Fill collision data
		*data = new CollisionData();
		(*data)->maxNumContacts = 1;
		(*data)->numContactsLeft = (*data)->maxNumContacts;
		(*data)->contact = new Contact[(*data)->maxNumContacts];

		vec2 normal;
		
		if (orient1 == 0 && orient2 == 0 && orient3 == 0 && orient4 == 0)
			normal = -Utils::getSegmentNormal(seg2->getPosition(), seg1);
		else if (orient1 == 0)
		{
			if (orient2 == 1)
				normal = seg1->getOrthogonal();
			else
				normal = -seg1->getOrthogonal();
		}
		else if (orient2 == 0)
		{
			if (orient1 == 1)
				normal = seg1->getOrthogonal();
			else
				normal = -seg1->getOrthogonal();
		}
		else if (orient3 == 0)
		{
			if (orient4 == 1)
				normal = seg2->getOrthogonal();
			else
				normal = -seg2->getOrthogonal();
		}
		else if (orient4 == 0)
		{
			if (orient3 == 1)
				normal = seg2->getOrthogonal();
			else
				normal = -seg2->getOrthogonal();
		}
		else if (orient1 != orient2 && orient3 != orient4)
		{
			normal = -Utils::getSegmentNormal(seg2->getPosition(), seg1);
			if (all(isnan(normal)))
				normal = -Utils::getSegmentNormal(seg1->getPosition(), seg2);
		}

		if (obj1->getParams()->getInverseMass() < obj2->getParams()->getInverseMass())
		{
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj2, obj1 });
		}
		else
		{
			normal = -normal;
			(*data)->contact[0].setObjects(vector<PhysicsEntity*> { obj1, obj2 });
		}
		(*data)->contact[0].setContactNormal(normal);

		(*data)->contact[0].setRestitution(0.5f * (obj1->getParams()->getRestitution() + obj2->getParams()->getRestitution()));

		
		float penetration = 0.0f;

		(*data)->contact[0].setPenetration(penetration);
		(*data)->numContactsLeft--;
	}

	return collision;
}