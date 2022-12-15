#include "SpaceScene.h"

SpaceScene::SpaceScene(Camera _camera)
{
	m_camera = _camera;
}

SpaceScene::~SpaceScene()
{
	boxes.clear();
}

void SpaceScene::Init()
{
	m_meshes[0]->SetPosition({ 1.0f, 0.0f, 2.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.005f, 0.005f, 0.005f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.0008f, 0.0008f, 0.0008f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });

	m_meshes[2]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[2]->SetScale({ 0.003f, 0.003f, 0.003f });
	m_meshes[2]->SetPosition({ 0.0f, 0.0f, -2.0f });

}
void SpaceScene::ProcessInput(float dt)
{
	//if (Application::Mouse.GetMouseDown())
	//{
	//	float x = (float)(rand() % 10) - 5;
	//	float y = (float)(rand() % 10) - 5;
	//	float z = (float)(rand() % 10) - 5;

	//	Mesh* box = new Mesh();
	//	box->Create(m_shaders[0], "../Assets/Models/cube.obj");
	//	box->SetCameraPosition(m_camera.GetPosition());
	//	box->SetScale({ 0.2f, 0.2f, 0.2f });
	//	box->SetSpecularStrength(4);
	//	box->SetPosition({ x,y,z });
	//	boxes.push_back(box);

	//	Application::Mouse.SetMouseDown(false);
	//}
}

void SpaceScene::Update(float dt)
{
	//for (unsigned int boxCount = 0; boxCount < boxes.size(); boxCount++)
	//{
	//	glm::vec3 curPos = boxes[boxCount]->GetPosition();
	//	if (glm::distance(glm::vec3(0, 0, 0), curPos) <= 0.1f)
	//	{
	//		boxes.erase(boxes.begin() + boxCount);
	//	}
	//	else
	//	{
	//		curPos += (glm::normalize(glm::vec3(0, 0, 0) - curPos) * 2.0f * dt);
	//		boxes[boxCount]->SetPosition(curPos);
	//	}
	//}

}

void SpaceScene::Render()
{
	glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
	m_skybox.Render(m_camera.GetProjection() * view);

	for (unsigned int meshCount = 0; meshCount < m_meshes.size(); meshCount++)
	{
		m_meshes[meshCount]->Render(m_camera.GetProjection() * m_camera.GetView());
	}

	//for (unsigned int boxCount = 0; boxCount < boxes.size(); boxCount++)
	//{
	//	boxes[boxCount]->Render(m_camera.GetProjection() * m_camera.GetView());
	//}
}