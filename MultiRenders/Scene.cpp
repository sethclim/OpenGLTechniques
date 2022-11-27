#include "Scene.h"

Scene::Scene()
{

}

Scene::Scene(Camera _camera)
{
	m_camera = _camera;
	m_meshes.clear();
	m_shaders.clear();
}

Scene::~Scene()
{

}

void Scene::AddMesh(Mesh* _mesh)
{
	m_meshes.push_back(_mesh);
}

void Scene::AddShader(Shader* _shader)
{
	m_shaders.push_back(_shader);
}

void Scene::ProcessInput(float _dt)
{

}
 
void Scene::Render()
{
	for (unsigned int meshCount = 0; meshCount < m_meshes.size(); meshCount++)
	{
		m_meshes[meshCount]->Render(m_camera.GetProjection() * m_camera.GetView());
	}
}
