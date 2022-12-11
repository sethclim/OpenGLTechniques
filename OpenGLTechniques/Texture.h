#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardIncludes.h"

class Texture
{
public:
	Texture();
	virtual ~Texture() { }

	GLuint GetTexture() { return m_texture; }

	void LoadTexture(std::string _fileName);
	void Cleanup();

private:
	int     m_width;
	int     m_height;
	int     m_channels;
	GLuint  m_texture;
};

#endif //TEXTURE_H
