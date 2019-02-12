#pragma once
#include <glm/glm.hpp>
#include "../GLCommon.h"
#include "../Shader.h"

struct DirectionalLight
{
	Vec3f Color;
	float AmbientIntensity;
	Vec3f Direction;
	float DiffuseIntensity;

	void Bind(Shader& shader)
	{
		shader.SetUniform("u_DirectionalLight.Color", Color);
		shader.SetUniform("u_DirectionalLight.AmbientIntensity", AmbientIntensity);
		shader.SetUniform("u_DirectionalLight.DiffuseIntensity", DiffuseIntensity);
		shader.SetUniform("u_DirectionalLight.Direction", glm::radians(Direction));
	}
};
