/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once

#include "Entity.h"
#include "PhysParameters.h"
class Collider;

class PhysicsEntity : public Entity
{
protected:
	PhysParameters* params = nullptr; 
	Collider* collider = nullptr;

private:
	float restitution;

public:
	~PhysicsEntity() 
	{ 
		if (params != nullptr)
		{
			delete params;
		}

		if (collider != nullptr)
		{
			delete collider; 
		}
	}

	virtual void update(float dt) = 0;
	virtual void draw(int width, int height) = 0;

	PhysParameters* getParams();
	void setParams(PhysParameters p);

	Collider* getCollider();
};