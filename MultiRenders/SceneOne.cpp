#include "ToolWindow.h"
#include "SceneOne.h"

SceneOne::SceneOne(Camera _camera)
{
	m_camera = _camera;
}

SceneOne::~SceneOne()
{

}

void SceneOne::Init()
{
	m_meshes[0]->SetPosition({ 1.0f, 0.0f, 1.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.005f, 0.005f, 0.005f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.02f, 0.02f, 0.02f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetSpecularStrength(MultiRenders::ToolWindow::specularStrength);
}

void SceneOne::ProcessInput(float dt)
{
	if (Application::Mouse.GetMouseDown())
	{
		glm::vec3 dir = Utilities::ViewToWorldCoordTransform(Application::Mouse.GetPosition(), m_camera);
		glm::vec2 pos = Application::Mouse.GetPosition();
		glm::vec3 _curLightPos = m_meshes[0]->GetPosition();
		_curLightPos += (dir * 0.5f * dt);

		m_meshes[0]->SetPosition(_curLightPos);
		m_meshes[1]->SetLightPosition(_curLightPos);
	}

	if (MultiRenders::ToolWindow::ResetLight)
	{
		m_meshes[0]->SetPosition({ 1.0f, 0.0f, 1.0f });

		MultiRenders::ToolWindow::ResetLight = false;
	}
}

void SceneOne::Update(float dt)
{
	m_meshes[1]->SetSpecularStrength(MultiRenders::ToolWindow::specularStrength);

	Mesh::Lights[0]->SetColor({
		MultiRenders::ToolWindow::color_R,
		MultiRenders::ToolWindow::color_G,
		MultiRenders::ToolWindow::color_B
	});

	glm::vec3 curRot = m_meshes[1]->GetRotation();

	curRot.x += 0.2f * dt;

	m_meshes[1]->SetRotation(curRot);

}