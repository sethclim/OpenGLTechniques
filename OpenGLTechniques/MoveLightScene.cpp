#include "ToolWindow.h"
#include "MoveLightScene.h"

MoveLightScene::MoveLightScene(Camera _camera)
{
	m_camera = _camera;
}

MoveLightScene::~MoveLightScene()
{

}

void MoveLightScene::Init()
{
	m_meshes[0]->SetPosition({ 1.0f, 0.0f, 2.0f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.005f, 0.005f, 0.005f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.002f, 0.002f, 0.002f });
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetSpecularStrength(OpenGLTechniques::ToolWindow::specularStrength);
}

void MoveLightScene::ProcessInput(float dt)
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

	if (OpenGLTechniques::ToolWindow::ResetLight)
	{
		m_meshes[0]->SetPosition({ 1.0f, 0.0f, 2.0f });

		OpenGLTechniques::ToolWindow::ResetLight = false;
	}
}

void MoveLightScene::Update(float dt)
{
	m_meshes[1]->SetSpecularStrength(OpenGLTechniques::ToolWindow::specularStrength);

	Mesh::Lights[0]->SetColor({
		OpenGLTechniques::ToolWindow::color_R,
		OpenGLTechniques::ToolWindow::color_G,
		OpenGLTechniques::ToolWindow::color_B
	});

	glm::vec3 curRot = m_meshes[1]->GetRotation();

	curRot.x += 0.2f * dt;

	m_meshes[1]->SetRotation(curRot);

}