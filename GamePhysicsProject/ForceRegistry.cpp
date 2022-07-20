/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "ForceRegistry.h"

using namespace std; 

void ForceRegistry::Add(PhysicsEntity* obj, Force* fg)
{
	ForceRegistration fr;
	fr.force = fg;
	fr.params = obj->getParams();
	registrations.push_back(fr);
}

void ForceRegistry::Remove(PhysicsEntity* obj, Force* fg)
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); it++) //iterates through the vector
	{
		if (it->params == obj->getParams()) //Check whether we found the entry we want to delete
		{
			registrations.erase(it); 	//if so erase it from the vector
			break;				//stop searching
		}
	}
}

void ForceRegistry::clear()
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); it++)
	{
		it->params->clearAccumulator();
	}
}

void ForceRegistry::updateForces(float dt)
{
	for (vector<ForceRegistration>::iterator it = registrations.begin(); it < registrations.end(); ++it)
	{
		it->force->updateForce(it->params, dt);
	}
}
