#include "WaterScene.h"

WaterScene::WaterScene(Camera _camera)
{
	m_camera = _camera;
}

WaterScene::~WaterScene()
{
	boxes.clear();
}

void WaterScene::Init()
{
	m_meshes[0]->SetPosition({ 1.0f, 0.0f, 4.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.01f, 0.01f, 0.01f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.05f, 0.05f, 0.05f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetSpecularStrength(4);
}

void WaterScene::ProcessInput(float dt)
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
	//	box->SetPosition({x,y,z});
	//	boxes.push_back(box);

	//	Application::Mouse.SetMouseDown(false);
	//}
}

void WaterScene::Update(float dt)
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
	//		curPos += (glm::normalize(glm::vec3(0,0,0) - curPos) * 2.0f * dt);
	//		boxes[boxCount]->SetPosition(curPos);
	//	}
	//}
}

void WaterScene::Render()
{
	//m_postProcessor.Start();

	Scene::Render();

	//m_postProcessor.End();
}