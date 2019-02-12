#include "TxaTexture.h"
#include "../Engine/GLCommon.h"
#include <fstream>
#include "../Engine/MemoryInputStream.h"
#include <vector>
#include <string>

TxaTexture::TxaTexture(char* textureData, int data_length)
{
	MemoryInputStream memoryInput(textureData, data_length);

	auto unkHeader = new char[20];
	memoryInput.get(unkHeader, 20);
	int unk1 = 0;
	memoryInput.get(unk1);
	int unk2 = 0;
	memoryInput.get(unk2);
	int unk3 = 0;
	memoryInput.get(unk3);
	short width = 0;
	memoryInput.get(width);
	short height = 0;
	memoryInput.get(height);
	short depth = 0;
	memoryInput.get(depth);


	std::vector<char> data;
	while (!memoryInput.Eof())
	{
		char val;
		memoryInput.get(val);
		data.push_back(val);
	}

	GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;

	switch (unk3)
	{
	case 12:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case 14:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	}


	CallGL(glGenTextures(1, &textureId));
	CallGL(glBindTexture(GL_TEXTURE_2D, textureId));


	CallGL(glCompressedTexImage2D(
		GL_TEXTURE_2D,
		0,
		format,
		width, /* width */
		height, /* height */
		0,
		size_dxtc(width, height, format),
		data.data() /* data */
	));


	CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	CallGL(glGenerateMipmap(GL_TEXTURE_2D));
}

void TxaTexture::Bind()
{
	CallGL(glBindTexture(GL_TEXTURE_2D, textureId));
}

