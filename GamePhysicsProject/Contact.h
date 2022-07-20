/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once

#include "glm\glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class PhysicsEntity;

class Contact
{
private:
	vector<PhysicsEntity*> objs;

	//vec2 contactPoint;
	vec2 contactNormal; 
	float restitution;
	float penetration;

	vec2 computeImpulse(float dt);
	void applyImpulse(vec2 impulse);

	void resolveVelocity(float dt);
	float resolveRestingContact(float dt);

public:

	void resolveInterpenetration(float dt);
	Contact() :penetration(0), restitution(0) {}
	virtual ~Contact(){}
	vec2 getContactNormal() const;

	void setObjects(vector<PhysicsEntity*> const& objects);
	void setRestitution(float rest);
	void setPenetration(float penetration);
	void setContactNormal(vec2 const& normal);

	float computeSeparatingVelocity() const;
	void resolveContacts(float dt);

};