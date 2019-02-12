#pragma once
#include <vector>
#include "MgaMesh.h"

class Moa
{
private:
	std::vector<MgaMesh*> submeshes;

public:
	Moa(char* meshData, int dataLength);

	void Draw(Shader& shader);
};
