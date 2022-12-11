#include "Mesh.h"
#include "Shader.h"

std::vector<Mesh*> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_texture = { };
	m_texture2 = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
}

Mesh::~Mesh()
{
	Lights.clear();
}

void Mesh::Create(Shader* _shader, std::string _file)
{
	m_shader = _shader;

	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed To Load Mesh")
	
	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
		}
	}

	std::string diffuseMap = Loader.LoadedMaterials[0].map_Kd;
	const size_t last_slash_idx = diffuseMap.find_last_of("\\");

	if (std::string::npos != last_slash_idx)
	{
		diffuseMap.erase(0, last_slash_idx + 1);
	}

	std::string specularMap = Loader.LoadedMaterials[0].map_Ks;
	const size_t last_slash_idx2 = specularMap.find_last_of("\\");

	if (std::string::npos != last_slash_idx2)
	{
		specularMap.erase(0, last_slash_idx2 + 1);
	}

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/" + diffuseMap);

	m_texture2 = Texture();
	m_texture2.LoadTexture("../Assets/Textures/" + specularMap);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2,0,3,2,1,0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_indexData.size() * sizeof(float), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::CleanUp()
{
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
	m_texture2.Cleanup();
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0), m_position);
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);

	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[",  i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
		m_shader->SetVec3(Concat("light[",  i, "].diffuseColor").c_str(), Lights[i]->GetColor());
		m_shader->SetVec3(Concat("light[",  i, "].specularColor").c_str(), {3.0f, 3.0f, 3.0f});

		m_shader->SetVec3(Concat("light[",  i, "].position").c_str(), Lights[i]->GetPosition());
		m_shader->SetVec3(Concat("light[",  i, "].direction").c_str(), glm::normalize(glm::vec3({0.0f + i * 0.1f, 0, 0.0f + i * 0.1f}) - Lights[i]->GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
	}

	m_shader->SetFloat("material.specularStrength", m_specularStrength);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());
}
void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices() /* The attribute we want to configure*/,
		3/*size*/,
		GL_FLOAT/*type*/,
		GL_FALSE/*normalized*/,
		8 * sizeof(float)/*stride*/,
		(void*)0/*array buffer offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(
		m_shader->GetAttrNormals() /* The attribute we want to configure*/,
		3/*size*/,
		GL_FLOAT/*type*/,
		GL_FALSE/*normalized*/,
		8 * sizeof(float)/*stride*/,
		(void*)(3 * sizeof(float))/*array buffer offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(
		m_shader->GetAttrTexCoords() /* The attribute we want to configure*/,
		2/*size*/,
		GL_FLOAT/*type*/,
		GL_FALSE/*normalized*/,
		8 * sizeof(float)/*stride*/,
		(void*)(6 * sizeof(float))/*array buffer offset*/);
}

std::string Mesh::Concat(std::string _s1, int _index, std::string _s2)
{
	std::string index = std::to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}

