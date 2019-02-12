#include "Mesh.h"
#include <GL/glew.h>
#include "GLCommon.h"
#include "ObjReader.h"


void Mesh::Create(const std::vector<Vec3f>& vertexPositions, const std::vector<Vec3f>& normals, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs)
{
	indexCount = indices.size();
	CallGL(glGenVertexArrays(1, &vao));
	CallGL(glBindVertexArray(vao));


	GLuint vertexBuffer;
	CallGL(glGenBuffers(1, &vertexBuffer));
	CallGL(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	CallGL(glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(vertexPositions[1]), vertexPositions.data(), GL_STATIC_DRAW));
	CallGL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
	CallGL(glEnableVertexAttribArray(0));

	GLuint normalBuffer;
	CallGL(glGenBuffers(1, &normalBuffer));
	CallGL(glBindBuffer(GL_ARRAY_BUFFER, normalBuffer));
	CallGL(glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[1]), normals.data(), GL_STATIC_DRAW));
	CallGL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr));
	CallGL(glEnableVertexAttribArray(1));

	GLuint texCoordBuffer;
	CallGL(glGenBuffers(1, &texCoordBuffer));
	CallGL(glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer));
	CallGL(glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[1]), uvs.data(), GL_STATIC_DRAW));
	CallGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr));
	CallGL(glEnableVertexAttribArray(2));

	CallGL(glGenBuffers(1, &ibo));
	CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	CallGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[1]), indices.data(), GL_STATIC_DRAW));
}

Mesh::Mesh(const std::string& filepath)
{
	std::cout << "Loading model: " << filepath.c_str() << std::endl;
	auto model = ObjReader(filepath).ToIndexModel();
	Create(model.positions, model.normals, model.indices, model.texCoords);
}

void Mesh::Draw()
{
	CallGL(glBindVertexArray(vao));
	CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	CallGL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}

void Mesh::Bind()
{
	CallGL(glBindVertexArray(vao));
}

void Mesh::BindIbo()
{
	CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
}

int Mesh::GetIndexCount()
{
	return indexCount;
}

void Mesh::Delete()
{
	std::cout << "Deleting Mesh" << std::endl;
	CallGL(glDeleteBuffers(1, &ibo));
	CallGL(glDeleteVertexArrays(1, &vao));
}



