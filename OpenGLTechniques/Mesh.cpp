#include "Mesh.h"
#include "Shader.h"
#include "Utilities.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

std::vector<Mesh *> Mesh::Lights;

Mesh::Mesh()
{
	m_shader = nullptr;
	m_textureDiffuse = {};
	m_textureSpecular = {};
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = {0, 0, 0};
	m_rotation = {0, 0, 0};
	m_scale = {1, 1, 1};
	m_world = glm::mat4();
	m_instanceCount = 1;
	m_enableInstancing = false;
	m_elementSize = 0;
}

Mesh::~Mesh()
{
}

std::string Mesh::RemoveFolder(std::string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}

	return _map;
}

void Mesh::CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3 &_tangent, objl::Vector3 &_bitangent)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}

void Mesh::loadModel(std::string _file)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _file.c_str()))
	{
		throw std::runtime_error(warn + err);
	}

	std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
	std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
	std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2) << std::endl;

	m_enableNormalMap = false;

	//for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
	//{
	//	//printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
	//	//	   static_cast<const double>(attrib.vertices[3 * v + 0]),
	//	//	   static_cast<const double>(attrib.vertices[3 * v + 1]),
	//	//	   static_cast<const double>(attrib.vertices[3 * v + 2]));
	//}

	//for (size_t v = 0; v < attrib.normals.size() / 3; v++)
	//{
	//	//printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
	//	//	   static_cast<const double>(attrib.normals[3 * v + 0]),
	//	//	   static_cast<const double>(attrib.normals[3 * v + 1]),
	//	//	   static_cast<const double>(attrib.normals[3 * v + 2]));
	//}

	//printf("shapes.size() %ld\n", static_cast<long>(shapes.size()));

	for (size_t i = 0; i < shapes.size(); i++)
	{
		size_t index_offset = 0;
		//printf("sshapes[i].mesh.num_face_vertices.size() %ld\n", static_cast<long>(shapes[i].mesh.num_face_vertices.size()));
		// For each face
		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++)
		{
			size_t fnum = shapes[i].mesh.num_face_vertices[f];

			//printf("  face[%ld].fnum = %ld\n", static_cast<long>(f),
			//	   static_cast<unsigned long>(fnum));

			// For each vertex in the face
			for (size_t v = 0; v < fnum; v++)
			{
				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];
	/*			printf("    face[%ld].v[%ld].idx = %d/%d/%d\n", static_cast<long>(f),
					   static_cast<long>(v), idx.vertex_index, idx.normal_index,
					   idx.texcoord_index);*/

				m_vertexData.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
				m_vertexData.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
				m_vertexData.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

				m_vertexData.push_back(attrib.normals[3 * idx.normal_index + 0]);
				m_vertexData.push_back(attrib.normals[3 * idx.normal_index + 1]);
				m_vertexData.push_back(attrib.normals[3 * idx.normal_index + 2]);

				m_vertexData.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
				m_vertexData.push_back(1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]);
			}

			/*	printf("  face[%ld].material_id = %d\n", static_cast<long>(f),
					   shape.mesh.material_ids[f]);
				printf("  face[%ld].smoothing_group_id = %d\n", static_cast<long>(f),
					   shape.mesh.smoothing_group_ids[f]);*/

			index_offset += fnum;
		}
	}
}

void Mesh::Create(Shader *_shader, std::string _file, int _instanceCount, bool indexed)
{
	m_shader = _shader;
	m_instanceCount = _instanceCount;
	if (m_instanceCount > 1)
	{
		m_enableInstancing = true;
	}
	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed To Load Mesh")

	if (indexed)
	{
		loadModel(_file);
	}
	else
	{
		for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = Loader.LoadedMeshes[i];
			std::vector<objl::Vector3> tangents;
			std::vector<objl::Vector3> bitangents;
			std::vector<objl::Vertex> triangle;

			objl::Vector3 tangent;
			objl::Vector3 bitangent;

			for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
			{
				triangle.clear();
				triangle.push_back(curMesh.Vertices[j]);
				triangle.push_back(curMesh.Vertices[j + 1]);
				triangle.push_back(curMesh.Vertices[j + 2]);
				CalculateTangents(triangle, tangent, bitangent);
				tangents.push_back(tangent);
				bitangents.push_back(bitangent);
			}

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

				if (Loader.LoadedMaterials[0].map_bump != "")
				{
					int index = j / 3;
					m_vertexData.push_back(tangents[index].X);
					m_vertexData.push_back(tangents[index].Y);
					m_vertexData.push_back(tangents[index].Z);

					m_vertexData.push_back(bitangents[index].X);
					m_vertexData.push_back(bitangents[index].Y);
					m_vertexData.push_back(bitangents[index].Z);
				}
				// std::cout << curMesh.Vertices[j].Position.X << " " << curMesh.Vertices[j].Position.Y << " " << curMesh.Vertices[j].Position.Z << std::endl;
			}
		}
	}

	// m_textureDiffuse = Texture();
	// m_textureDiffuse.LoadTexture("./Debug/Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Kd));

	// m_textureSpecular = Texture();
	// if (Loader.LoadedMaterials[0].map_Ks != "")
	//{
	//	m_textureSpecular.LoadTexture("./Debug/Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_Ks));
	// }

	// m_textureNormal = Texture();
	// if (Loader.LoadedMaterials[0].map_bump != "")
	//{
	//	m_textureNormal.LoadTexture("./Debug/Assets/Textures/" + RemoveFolder(Loader.LoadedMaterials[0].map_bump));
	//	m_enableNormalMap = true;
	// }

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime());
		for (unsigned int i = 0; i < m_instanceCount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(Utilities::GetRandomWithExclusion(-2000, 4000, -200, 200),
													Utilities::GetRandomWithExclusion(-2000, 4000, -200, 200),
													Utilities::GetRandomWithExclusion(-2000, 4000, -200, 200)));

			model = glm::rotate(model, glm::radians((float)(rand() % 360)), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians((float)(rand() % 360)), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians((float)(rand() % 360)), glm::vec3(0, 0, 1));

			float size = (float)(rand() % 10 + 1);

			model = glm::scale(model, glm::vec3(size, size, size));

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m_instanceData.push_back(model[x][y]);
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, m_instanceCount * sizeof(glm::mat4), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// m_indexData = {
	//	2,0,3,2,1,0
	// };

	// glGenBuffers(1, &m_indexBuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
	// glBufferData(GL_ARRAY_BUFFER, m_indexData.size() * sizeof(float), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::CleanUp()
{
	// glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0), m_position);
	m_world = glm::rotate(m_world, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_world = glm::rotate(m_world, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

	for (unsigned int i = 0; i < Lights.size(); i++)
	{
		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), {0.5f, 0.5f, 0.5f});
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i]->GetColor());
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), Lights[i]->GetLightSpecularColor());

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i]->GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({0.0f + i * 0.1f, 0, 0.0f + i * 0.1f}) - Lights[i]->GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
	}

	m_shader->SetFloat("material.specularStrength", GetSpecularStrength());
	// m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	// m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	// m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	int stride = 8;

	if (m_enableNormalMap)
	{
		stride += 6;
	}

#pragma region BindVertexData
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices() /* The attribute we want to configure*/,
		3 /*size*/,
		GL_FLOAT /*type*/,
		GL_FALSE /*normalized*/,
		stride * sizeof(float) /*stride*/,
		(void *)0 /*array buffer offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(
		m_shader->GetAttrNormals() /* The attribute we want to configure*/,
		3 /*size*/,
		GL_FLOAT /*type*/,
		GL_FALSE /*normalized*/,
		stride * sizeof(float) /*stride*/,
		(void *)(3 * sizeof(float)) /*array buffer offset*/);

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(
		m_shader->GetAttrTexCoords() /* The attribute we want to configure*/,
		2 /*size*/,
		GL_FLOAT /*type*/,
		GL_FALSE /*normalized*/,
		stride * sizeof(float) /*stride*/,
		(void *)(6 * sizeof(float)) /*array buffer offset*/);

	m_elementSize = 8;
#pragma endregion

#pragma region BindNormalData
	if (m_enableNormalMap)
	{
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(m_shader->GetAttrTangents(),
							  3,
							  GL_FLOAT,
							  GL_FALSE,
							  stride * sizeof(float),
							  (void *)(8 * sizeof(float)));
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(m_shader->GetAttrBitangents(),
							  3,
							  GL_FLOAT,
							  GL_FALSE,
							  stride * sizeof(float),
							  (void *)(11 * sizeof(float)));
		m_elementSize += 6;
	}
#pragma endregion

#pragma region BindInstancingData
	if (m_enableInstancing)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix(),
							  4,
							  GL_FLOAT,
							  GL_FALSE,
							  sizeof(glm::mat4),
							  (void *)0);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 1,
							  4,
							  GL_FLOAT,
							  GL_FALSE,
							  sizeof(glm::mat4),
							  (void *)(sizeof(glm::vec4)));

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 2,
							  4,
							  GL_FLOAT,
							  GL_FALSE,
							  sizeof(glm::mat4),
							  (void *)(2 * sizeof(glm::vec4)));

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 3,
							  4,
							  GL_FLOAT,
							  GL_FALSE,
							  sizeof(glm::mat4),
							  (void *)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix(), 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 1, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 2, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 3, 1);
	}
#pragma endregion
}

std::string Mesh::Concat(std::string _s1, int _index, std::string _s2)
{
	std::string index = std::to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	// m_rotation.x += 0.1f;

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	if (m_enableInstancing)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize, m_instanceCount);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize);
	}

	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());

	if (m_enableNormalMap)
	{
		glDisableVertexAttribArray(m_shader->GetAttrTangents());
		glDisableVertexAttribArray(m_shader->GetAttrBitangents());
	}

	if (m_enableInstancing)
	{
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
	}
}
