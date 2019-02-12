#pragma once
#include <string>
#include <GL/glew.h>

class Texture
{
private:
	GLuint textureId;

public:
	Texture(const std::string& filename);
	void Bind();
	void Unbind();

	void Delete();
};
