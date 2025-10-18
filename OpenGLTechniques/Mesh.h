#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return m_position; }

	void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
	glm::vec3 GetRotation() { return m_rotation; }

	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	glm::vec3 GetScale() { return m_scale; }

	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetSpecularStrength(float _specularStrength) { m_specularStrength = _specularStrength; }
	float GetSpecularStrength() { return m_specularStrength; }
	void SetLightPosition(glm::vec3 _lightPosition) { m_lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetLightSpecularColor(glm::vec3 _lightSpecularColor) { m_lightSpecularColor = _lightSpecularColor; }
	glm::vec3 GetLightSpecularColor() { return m_lightSpecularColor; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }

	void loadModel(std::string _file);
	void Create(Shader *_shader, std::string _file, int _iostanceCount = 1, bool indexed = false);
	void CleanUp();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

	static std::vector<Mesh *> Lights;

private:
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	std::string Concat(std::string _s1, int _index, std::string _s2);
	std::string RemoveFolder(std::string _map);
	void CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3 &_tangent, objl::Vector3 &_bitangent);

	Shader *m_shader;
	Texture m_textureDiffuse;
	Texture m_textureSpecular;
	Texture m_textureNormal;

	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	GLuint m_instanceBuffer;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;
	std::vector<GLfloat> m_instanceData;
	bool m_enableNormalMap;
	int m_instanceCount;
	bool m_enableInstancing;
	int m_elementSize;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;

	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;
	glm::vec3 m_lightSpecularColor;
	float m_specularStrength;
};
#endif // !MESH_H
