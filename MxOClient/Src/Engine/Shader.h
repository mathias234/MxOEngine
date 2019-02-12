#pragma once
#include <string>
#include "Common.h"
#include <gl/glew.h>
#include <glm/mat4x4.hpp>
#include "GLCommon.h"

struct ShaderProgramSource
{
	std::string vertex_source;
	std::string fragment_source;
};


class Shader {

public:
	Shader(const std::string& path);

	void Bind();

	void SetUniform(const char* uniformName, glm::vec4 vector4);
	void SetUniform(const char* uniformName, Vec3f vector3);
	void SetUniform(const char* uniformName, glm::vec2 vector2);
	void SetUniform(const char* uniformName, float value);
	void SetUniform(const char* uniformName, glm::mat4 matrix4);

	void Delete();
private:
	int shaderId;

	static ShaderProgramSource ParseShader(const std::string& filepath);
	static GLuint CompileShader(GLuint type, const std::string& source);
	static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};