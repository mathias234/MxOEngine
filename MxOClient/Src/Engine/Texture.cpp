#include "Texture.h"
#include "GLCommon.h"

Texture::Texture(const std::string& filename)
{
	std::string filepath = "data/textures/" + filename;
	std::cout << "Loading texture: " << filepath.c_str() << std::endl;

	//sf::Image image;
	//image.loadFromFile(filepath);
	//CallGL(glGenTextures(1, &textureId));
	//CallGL(glBindTexture(GL_TEXTURE_2D, textureId));

	//CallGL(glTexImage2D(
	//	GL_TEXTURE_2D,
	//	0,
	//	GL_RGBA,
	//	image.getSize().x,
	//	image.getSize().y,
	//	0,
	//	GL_RGBA,
	//	GL_UNSIGNED_BYTE,
	//	image.getPixelsPtr()));

	//CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	//CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	//CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	//CallGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//CallGL(glGenerateMipmap(GL_TEXTURE_2D));
}

void Texture::Bind()
{
}

void Texture::Unbind()
{
}

void Texture::Delete()
{
}
