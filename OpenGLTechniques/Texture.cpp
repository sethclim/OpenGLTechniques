#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	m_width = 0;
	m_height = 0;
	m_channels = 0;
	m_textureDiffuse = 0;
}

void Texture::Cleanup()
{
	glDeleteTextures(1, &m_textureDiffuse);
}

bool Texture::EndsWith(const std::string &_str, const std::string &_suffix)
{
	bool res = _str.substr(_str.size() - 4) == _suffix;
	return res;
}

void Texture::LoadTexture(std::string _fileName)
{
	glGenTextures(1, &m_textureDiffuse);
	glBindTexture(GL_TEXTURE_2D, m_textureDiffuse);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	GLubyte *data = stbi_load(_fileName.c_str(), &m_width, &m_height, &m_channels, 0);
	M_ASSERT(data != nullptr, "Failed to load texture");

	GLenum format = 0;
	if (m_channels == 1)
		format = GL_RED;
	else if (m_channels == 3)
		format = GL_RGB;
	else if (m_channels == 4)
		format = GL_RGBA;
	else
		M_ASSERT(false, "Unsupported texture channel count");

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::LoadCubeMap(std::vector<std::string> _faces)
{
	glGenTextures(1, &m_textureDiffuse);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureDiffuse);

	for (unsigned int i = 0; i < _faces.size(); i++)
	{
		stbi_set_flip_vertically_on_load(false);
		GLubyte *data = stbi_load(_faces[i].c_str(), &m_width, &m_height, &m_channels, 0);

		M_ASSERT(data != nullptr, "Failed to load cubemap texture");

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
