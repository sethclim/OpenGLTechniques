#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"


class Skybox
{
public:
	Skybox();
	virtual ~Skybox();

	void Create(Shader* _shader, std::string _file, std::vector<std::string> _faces);
	void CleanUp();
	void Render(glm::mat4 _pv);

private:
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttibutes();

	Shader* m_shader;
	Texture m_textureDiffuse;
	GLuint  m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
};

#endif // !SKYBOX_H
