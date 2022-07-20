/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Contact.h"
#include "PhysicsEntity.h"
#include "Utils.h"
#include <iostream>
using namespace std;

void Contact::resolveVelocity(float dt)
{
	applyImpulse(computeImpulse(dt));
}

void Contact::applyImpulse(vec2 impulse)
{
	if (length(impulse) != 0)
	{
		objs[0]->getParams()->velocity += impulse * objs[0]->getParams()->getInverseMass();
		if (objs[1])
			objs[1]->getParams()->velocity -= impulse * objs[1]->getParams()->getInverseMass();
	}
}

vec2 Contact::computeImpulse(float dt)
{
	float separatingVelocity = computeSeparatingVelocity();
	if (separatingVelocity > 0) return vec2(0);

	float newSepVel = -separatingVelocity * (1 + restitution) - resolveRestingContact(dt);
	if (newSepVel < 0) newSepVel = 0;

	float totalInvMass = objs[0]->getParams()->getInverseMass();
	if (objs[1]) totalInvMass += objs[1]->getParams()->getInverseMass();
	if (totalInvMass < 0) return vec2(0);

	float impulseLenght = newSepVel / totalInvMass;
	return impulseLenght * contactNormal;
}

void Contact::resolveInterpenetration(float dt)
{
	if (penetration >= 0) return;

	float totalInvMass = objs[0]->getParams()->getInverseMass();
	if (objs[1]) totalInvMass += objs[1]->getParams()->getInverseMass();
	if (totalInvMass <= 0) return;

	vec2 movePerUnitMass = contactNormal * (-penetration / totalInvMass);
	
	objs[0]->getParams()->transform.Translate(0.5f*(movePerUnitMass * objs[0]->getParams()->getInverseMass()));
	objs[0]->getParams()->velocity += 0.5f * dot((movePerUnitMass * objs[0]->getParams()->getInverseMass()) / dt, contactNormal)*contactNormal;
	if (objs[1])
	{
		objs[1]->getParams()->transform.Translate(0.5f*(movePerUnitMass * objs[1]->getParams()->getInverseMass()));
		objs[1]->getParams()->velocity -= 0.5f * dot((movePerUnitMass * objs[1]->getParams()->getInverseMass()) / dt, contactNormal) * contactNormal;
	}
}

float Contact::resolveRestingContact(float dt)
{
	vec2 accCausedVel = objs[0]->getParams()->acceleration;
	if (objs[1]) accCausedVel += objs[1]->getParams()->acceleration;
	float accCausedSepVel = dot(accCausedVel, contactNormal) * dt;

	if (accCausedSepVel < 0)
	{
		return accCausedSepVel;
	}
	else
		return 0;

}

vec2 Contact::getContactNormal() const
{
	return contactNormal;
}

float Contact::computeSeparatingVelocity() const
{
	vec2 relVelocity = objs[0]->getParams()->velocity;
	if (objs[1]) relVelocity -= objs[1]->getParams()->velocity;
	return dot(relVelocity, contactNormal);
}

void Contact::resolveContacts(float dt)
{
	resolveVelocity(dt);
	resolveInterpenetration(dt);
}

void Contact::setObjects(vector<PhysicsEntity*> const& objects)
{
	objs = objects;
}

void Contact::setRestitution(float rest)
{
	restitution = Utils::clamp(rest);
}

void Contact::setPenetration(float penetration)
{
	if (penetration < 0)
		Contact::penetration = penetration;
	else
		penetration = 0;
}

void Contact::setContactNormal(vec2 const& normal)
{
	contactNormal = normal;
}
