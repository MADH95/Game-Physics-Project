#pragma once

#include "PhysParameters.h"

class Force
{
public:
	virtual ~Force() {}

	virtual void updateForce(PhysParameters *obj, float dt) = 0
	{

	}
};