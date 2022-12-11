#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardIncludes.h"

class Texture
{
public:
	Texture();
	virtual ~Texture() { }

	GLuint GetTexture() { return m_textureDiffuse; }

	void LoadTexture(std::string _fileName);
	void LoadCubeMap(std::vector<std::string> _faces);
	void Cleanup();

private:
	int     m_width;
	int     m_height;
	int     m_channels;
	GLuint  m_textureDiffuse;

	bool EndsWith(const std::string& _str, const std::string& _suffix);
};

#endif //TEXTURE_H
