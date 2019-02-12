#include "MgaMesh.h"
#include "../Engine/MemoryInputStream.h"
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "../Engine/GLCommon.h"


MgaMesh::MgaMesh(char* meshData, int data_length, TxaTexture* txaTex, TxaTexture* color)
{
	texture = txaTex;
	colorTex = color;
	MemoryInputStream memoryInput(meshData, data_length);

	auto unkHeader = new char[23];
	memoryInput.get(unkHeader, 23);
	delete[] unkHeader;

	short unk0Buffer = 0;
	memoryInput.get(unk0Buffer);

	short unk1Buffer = 0;
	memoryInput.get(unk1Buffer);

	short vertexCount = 0;
	memoryInput.get(vertexCount);

	short unk2Buffer = 0;
	memoryInput.get(unk2Buffer);

	short indexCount = 0;
	memoryInput.get(indexCount);

	auto unkBuffer = new char[30];
	memoryInput.get(unkBuffer, 30);
	delete[] unkBuffer;

	std::vector<Vec3f> vertices;
	std::vector<Vec3f> normals;
	std::vector<glm::vec2> uvs;
	for (int i = 0; i < vertexCount; ++i)
	{
		float posX = 0;
		float posY = 0;
		float posZ = 0;
		float normX = 0;
		float normY = 0;
		float normZ = 0;
		float u = 0;
		float v = 0;

		memoryInput.get(posX);
		memoryInput.get(posY);
		memoryInput.get(posZ);
		memoryInput.get(normX);
		memoryInput.get(normY);
		memoryInput.get(normZ);
		memoryInput.get(u);
		memoryInput.get(v);

		vertices.push_back({ posX, posY, posZ });
		normals.push_back({ normX, normY, normZ });
		uvs.push_back({ u, v });
	}

	std::vector<unsigned short> indices;

	while(!memoryInput.Eof()) {
		short index = 0;

		memoryInput.get(index);

		indices.push_back(index);
	}
	index_count_ = indices.size();

	CallGL(glGenVertexArrays(1, &vao));
	CallGL(glBindVertexArray(vao));

	GLuint vertexBuffer;
	CallGL(glGenBuffers(1, &vertexBuffer));
	CallGL(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	CallGL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[1]), vertices.data(), GL_STATIC_DRAW));
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


void MgaMesh::Draw(Shader& shader)
{
	if (texture != nullptr)
		texture->Bind();

	if (colorTex != nullptr)
		colorTex->Bind();

	CallGL(glBindVertexArray(vao));
	CallGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	CallGL(glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_SHORT, nullptr));

}
