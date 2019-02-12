#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "GLCommon.h"

class Entity;

class Camera
{
private:
	Vec3f pos;
	Vec3f rot;
public:
	void Update(float deltaTime);
	void SetPosition(Vec3f position);
	void SetRotation(Vec3f rotation);

	Vec3f  GetPosition();
	Vec3f  GetRotation();
};
