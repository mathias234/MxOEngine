#pragma once
#include "Common.h"
#include <vector>
#include <gl/glew.h>
#include <glm/detail/type_vec2.hpp>
#include "GLCommon.h"

class Mesh
{
private:
	GLuint vao;
	GLuint ibo;
	int indexCount;
	void Create(const std::vector<Vec3f>& vertexPositions, const std::vector<Vec3f>& normals, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs);
public:
	Mesh(const std::string& filepath);
	void Draw();

	int GetIndexCount();

	void Bind();
	void BindIbo();

	void Delete();
};
