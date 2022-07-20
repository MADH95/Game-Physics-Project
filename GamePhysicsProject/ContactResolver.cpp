/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "ContactResolver.h"

void ContactResolver::setNumIterations(int numIterations)
{
	ContactResolver::numIterations = numIterations;
}

void ContactResolver::resolveContacts(Contact * contactArray, int numContacts, float dt)
{
	iteration = 0;
	int maxIndex = numContacts;
	while (iteration < numIterations) {
		float max = 0;
		maxIndex = numContacts;
		for (int i = 0; i < numContacts; i++) {
			float sepVel = contactArray[i].computeSeparatingVelocity();
			if (sepVel < max) {
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex < numContacts)
			contactArray[maxIndex].resolveContacts(dt);	
		iteration++;
	}

}
