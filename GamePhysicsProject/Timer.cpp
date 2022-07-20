/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Timer.h"

LowResTimer::LowResTimer()
{
	
}

void LowResTimer::startTimer()
{
	timer = clock();
}

double LowResTimer::getTime()
{
	return ((double)(clock() - timer)) / CLOCKS_PER_SEC;
}

void LowResTimer::resetTimer()
{
	startTimer();
}
