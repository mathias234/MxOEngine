#pragma once

#include <glm/glm.hpp>

namespace Math {
	glm::mat4 CreateViewMatrix(Vec3f position, Vec3f rotation);
	glm::mat4 CreateModelMatrix(Vec3f position, Vec3f rotation, Vec3f scale);
	glm::mat4 CreateProjMatrix();
};