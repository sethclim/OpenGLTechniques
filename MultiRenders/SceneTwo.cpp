#include "SceneTwo.h"

SceneTwo::SceneTwo(Camera _camera)
{
	m_camera = _camera;
}

SceneTwo::~SceneTwo()
{

}

void SceneTwo::Init()
{
	m_meshes[0]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[0]->SetScale({ 0.01f, 0.01f, 0.01f });
	m_meshes[0]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[0]->SetSpecularStrength(8.0f);
}

void SceneTwo::ProcessInput(float dt)
{
	if (Application::Mouse.GetMouseDown())
	{
		glm::vec3 dir = Utilities::ViewToWorldCoordTransform(Application::Mouse.GetPosition(), m_camera);
		glm::vec2 pos = Application::Mouse.GetPosition();
		glm::vec3 _curTeaPotPos = m_meshes[0]->GetPosition();
		_curTeaPotPos += (dir * 0.5f * dt);

	    m_meshes[0]->SetPosition(_curTeaPotPos);
	}
}