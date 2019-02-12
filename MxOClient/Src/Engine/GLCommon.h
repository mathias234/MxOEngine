#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>


typedef glm::vec3 Vec3f;

#define ASSERT(x) if(!(x)) __debugbreak();

#define CallGL(x) GLClearError();\
	    x;\
        ASSERT(GLError(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLError(const char* func_name, const char* file, const int line)
{
	while (GLenum error = glGetError())
	{
		const char* errorMessage = "unknown error";
		switch (error)
		{
		case GL_INVALID_ENUM:
			errorMessage = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorMessage = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorMessage = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			errorMessage = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			errorMessage = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			errorMessage = "GL_OUT_OF_MEMORY";
		}

		std::cout << "OGL ERROR: " << errorMessage << " : " << func_name << " : " << file << " : " << line << std::endl;
		return false;
	}

	return true;
}


