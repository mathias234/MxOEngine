#pragma once
#include <gl/glew.h>
#include "TxaTexture.h"
#include <glm/detail/type_vec3.hpp>
#include "../Engine/Shader.h"

struct Vertex
{
	float posX;
	float posY;
	float posZ;

	float normX;
	float normY;
	float normZ;

	float unk7;
	float unk8;
};

class MgaMesh
{
private:
	GLuint vao;
	GLuint ibo;
	int index_count_;
	TxaTexture* texture;
	TxaTexture* colorTex;
public:
	MgaMesh(char* textureData, int data_length, TxaTexture* tex, TxaTexture* color);
	void Draw(Shader& shader);
};