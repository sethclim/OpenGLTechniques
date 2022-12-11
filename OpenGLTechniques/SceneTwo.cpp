#include "SceneTwo.h"
#include "ToolWindow.h"

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
	m_meshes[0]->SetScale({ 0.02f, 0.02f, 0.02f });
	m_meshes[0]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[0]->SetSpecularStrength(8.0f);
}

void SceneTwo::ProcessInput(float dt)
{
	glm::vec2 pos = Application::Mouse.GetPosition();
	if (Application::Mouse.GetMouseDown())
	{
		glm::vec3 dir = Utilities::ViewToWorldCoordTransform(pos, m_camera);
		glm::vec3 _curTeaPotPos = m_meshes[0]->GetPosition();
		_curTeaPotPos += (dir * 0.5f * dt);

	    m_meshes[0]->SetPosition(_curTeaPotPos);
	}

	if (MultiRenders::ToolWindow::ResetTeapot)
	{
		m_meshes[0]->SetPosition({ 0.0f, 0.0f, 0.0f });

		MultiRenders::ToolWindow::ResetTeapot = false;
	}

	
	glm::vec3 teaPotPos = m_meshes[0]->GetPosition();

	if (Application::Mouse.GetScroll() > 0)
	{
		teaPotPos.z += 0.1;
		m_meshes[0]->SetPosition(teaPotPos);
		Application::Mouse.SetScroll(0);
	}
	else if(Application::Mouse.GetScroll() < 0)
	{
		teaPotPos.z -= 0.1;
		Application::Mouse.SetScroll(0);
		m_meshes[0]->SetPosition(teaPotPos);
	}
}