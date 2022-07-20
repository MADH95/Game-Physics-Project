/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include "Contact.h"

class ContactResolver {
private:
	int numIterations;
	int iteration;

public:
	ContactResolver() :numIterations(0) {}

	void setNumIterations(int numIterations);
	void resolveContacts(Contact* contactArray, int numContacts, float dt);
};
