
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

namespace Math
{
	glm::mat4 CreateViewMatrix(Vec3f position, Vec3f rotation)
	{
		glm::mat4 matrix;
		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

		matrix = glm::translate(matrix, -position);

		return matrix;
	}

	glm::mat4 CreateModelMatrix(Vec3f position, Vec3f rotation, Vec3f scale)
	{
		glm::mat4 matrix;

		matrix = glm::translate(matrix, position);
		matrix = glm::scale(matrix, scale);

		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

		return matrix;
	}

	glm::mat4 CreateProjMatrix()
	{
		return glm::perspective(glm::radians(60.0f), (float)Window::Width / (float)Window::Height, 0.1f, 100.0f);
	}
}
