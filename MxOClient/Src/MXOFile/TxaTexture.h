#pragma once
#include <gl/glew.h>
#include <vector>

struct Color
{
public:
	char red;
	char green;
	char blue;
	char alpha;
};


class TxaTexture
{
public:
	TxaTexture(char* textureData, int data_length);

	void Bind();
private:
	GLuint textureId;

	static inline unsigned int size_dxtc(const unsigned int width, const unsigned int height, const GLenum format) {
		auto mul = 16;

		if (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
			mul = 8;

		return ((width + 3) / 4) * ((height + 3) / 4) * (mul);
	}

};
