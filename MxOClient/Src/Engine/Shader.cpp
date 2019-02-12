#include "Shader.h"
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include "GLCommon.h"
#include <glm/gtc/type_ptr.hpp>
#include "Maths.h"


Shader::Shader(const std::string& path)
{
	auto shader = ParseShader(path);
	shaderId = CreateShader(shader.vertex_source, shader.fragment_source);
}

void Shader::Bind()
{
	CallGL(glUseProgram(shaderId));
}

void Shader::SetUniform(const char* uniformName, glm::vec4 vector4)
{
	Bind();
	CallGL(int uniformLoc = glGetUniformLocation(shaderId, uniformName));
	ASSERT(uniformLoc != -1);
	CallGL(glUniform4f(uniformLoc, vector4.x, vector4.y, vector4.y, vector4.w));
}

void Shader::SetUniform(const char* uniformName, Vec3f vector3)
{
	Bind();
	CallGL(int uniformLoc = glGetUniformLocation(shaderId, uniformName));
	ASSERT(uniformLoc != -1);
	CallGL(glUniform3f(uniformLoc, vector3.x, vector3.y, vector3.y));
}

void Shader::SetUniform(const char* uniformName, glm::vec2 vector2)
{
	Bind();
	CallGL(int uniformLoc = glGetUniformLocation(shaderId, uniformName));
	ASSERT(uniformLoc != -1);
	CallGL(glUniform2f(uniformLoc, vector2.x, vector2.y));
}


void Shader::SetUniform(const char* uniformName, float value)
{
	Bind();
	CallGL(int uniformLoc = glGetUniformLocation(shaderId, uniformName));
	ASSERT(uniformLoc != -1);
	CallGL(glUniform1f(uniformLoc, value));
}



void Shader::SetUniform(const char* uniformName, glm::mat4 matrix4)
{
	Bind();
	CallGL(int uniformLoc = glGetUniformLocation(shaderId, uniformName));
	ASSERT(uniformLoc != -1);
	CallGL(glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix4)));
}


ShaderProgramSource Shader::ParseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string & source)
{
	CallGL(GLuint id = glCreateShader(type));
	const char* src = source.c_str();
	CallGL(glShaderSource(id, 1, &src, nullptr));
	CallGL(glCompileShader(id));

	int result;

	CallGL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		CallGL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		CallGL(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;

		CallGL(glDeleteShader(id));

		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	CallGL(glAttachShader(program, vs));

	CallGL(glAttachShader(program, fs));

	CallGL(glLinkProgram(program));
	CallGL(glValidateProgram(program));

	CallGL(glDeleteShader(vs));
	CallGL(glDeleteShader(fs));

	return program;
}

void Shader::Delete()
{
	std::cout << "Deleting Texture" << std::endl;
	CallGL(glDeleteProgram(shaderId));
}
