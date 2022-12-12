#ifndef POSTPROCESOR_H
#define POSTPROCESOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	PostProcessor();
	virtual ~PostProcessor();

	void Create(Shader* _postShader);
	void CleanUp();
	void Start();
	void End();

	Shader* GetShader();

private:
	GLuint  m_framebuffer;
	GLuint  m_textureColorbuffer;
	GLuint  m_renderBufferObject;
	GLuint  m_vertexBuffer;
	Shader* m_postShader;

	void CreateVertics();
	void CreateBuffers();
	void BindVertices();
};

#endif // !POSTPROCESOR_H
