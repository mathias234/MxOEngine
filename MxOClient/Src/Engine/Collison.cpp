#include "Collision.h"

bool Collision::AtMapEdgeX(float x)
{
	if (x >= 10000 || x <= -10000)
		return true;

	return false;
}

bool Collision::AtMapEdgeZ(float z)
{
	if (z >= 10000 || z <= -10000)
		return true;
	return false;
}

