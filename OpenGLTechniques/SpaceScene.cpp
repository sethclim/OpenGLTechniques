#include "SpaceScene.h"

SpaceScene::SpaceScene(Camera _camera)
{
	m_camera = _camera;
}

SpaceScene::~SpaceScene()
{

}

void SpaceScene::Init()
{
	m_meshes[0]->SetPosition({ 1.0f, 0.0f, 2.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetLightSpecularColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.005f, 0.005f, 0.005f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.0008f, 0.0008f, 0.0008f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetRotation({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetSpecularStrength(2);

	m_meshes[2]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[2]->SetScale({ 0.003f, 0.003f, 0.003f });
	m_meshes[2]->SetPosition({ 0.0f, 0.0f, -2.0f });

}
void SpaceScene::ProcessInput(float dt)
{

}

void SpaceScene::Update(float dt)
{
	m_camera.Rotate(40 * dt);
}

void SpaceScene::Render()
{
	glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
	m_skybox.Render(m_camera.GetProjection() * view);

	for (unsigned int meshCount = 0; meshCount < m_meshes.size(); meshCount++)
	{
		m_meshes[meshCount]->Render(m_camera.GetProjection() * m_camera.GetView());
	}
}