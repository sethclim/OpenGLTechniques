#include "SceneThree.h"

SceneThree::SceneThree(Camera _camera)
{
	m_camera = _camera;
}

SceneThree::~SceneThree()
{

}

void SceneThree::Init()
{
	m_meshes[0]->SetPosition({ 3.0f, -3.0f, 1.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.1f, 0.1f, 0.1f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.05f, 0.05f, 0.05f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetSpecularStrength(4);
}
void SceneThree::ProcessInput(float dt)
{
	if (Application::Mouse.GetMouseDown())
	{
		float x = (float)(rand() % 20) - 10;
		float y = (float)(rand() % 20) - 10;
		float z = (float)(rand() % 20) - 10;

		Mesh* box = new Mesh();
		box->Create(m_shaders[0], "../Assets/Models/cube.obj");
		box->SetCameraPosition(m_camera.GetPosition());
		box->SetScale({ 0.1f, 0.1f, 0.1f });
		box->SetSpecularStrength(4);
		box->SetPosition({x,y,z});
		m_meshes.push_back(box);
		boxes.push_back(box);
	}
}

void SceneThree::Update(float dt)
{
	for (unsigned int boxCount = 0; boxCount < boxes.size(); boxCount++)
	{
		glm::vec3 curPos = boxes[boxCount]->GetPosition();
		if (glm::distance(glm::vec3(0, 0, 0), curPos) <= 0.1f)
		{
			boxes.erase(boxes.begin() + boxCount);
		}
		else
		{
			curPos += (glm::normalize(glm::vec3(0,0,0) - curPos) * 2.0f * dt);
			boxes[boxCount]->SetPosition(curPos);
		}
	}
}