#include "TransformScene.h"
#include "ToolWindow.h"

TransformScene::TransformScene(Camera _camera)
{
	m_camera = _camera;
}

TransformScene::~TransformScene()
{

}

void TransformScene::Init()
{
	m_meshes[0]->SetPosition({ 0.0f, 1.0f, 0.5f });
	m_meshes[0]->SetColor({ 1.0f, 1.0f,1.0f });
	m_meshes[0]->SetScale({ 0.006f, 0.006f, 0.006f });
	m_meshes[0]->SetLightSpecularColor({ 1.0f, 1.0f,1.0f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetRotation({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetScale({ 0.0008f, 0.0008f, 0.0008f });
	m_meshes[1]->SetSpecularStrength(2);
}

void TransformScene::ProcessInput(float dt)
{
	if (Application::Mouse.GetMouseDown())
	{
		glm::vec3 dir = Utilities::ViewToWorldCoordTransform(Application::Mouse.GetPosition(), m_camera);
		glm::vec2 pos = Application::Mouse.GetPosition();

		//Translate
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Translate)
		{
			glm::vec3 _fighterPosition = m_meshes[1]->GetPosition();
			_fighterPosition += (dir * 0.5f * dt);
			m_meshes[1]->SetPosition(_fighterPosition);
		}
		
		//Rotate
 		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Rotate)
		{
			glm::vec3 _fighterRotation = m_meshes[1]->GetRotation();
			_fighterRotation += (dir * 3.0f * dt);
			m_meshes[1]->SetRotation(_fighterRotation);
		}

		//Scale
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Scale)
		{
			glm::vec3 _fighterScale = m_meshes[1]->GetScale();
			_fighterScale += (dir * 0.0001f * dt);
			m_meshes[1]->SetScale(_fighterScale);
		}

	}

	if (Application::Mouse.GetMouseMiddleDown())
	{
		glm::vec3 dir = Utilities::ViewToWorldCoordTransform(Application::Mouse.GetPosition(), m_camera);
		glm::vec2 pos = Application::Mouse.GetPosition();

		//Translate
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Translate)
		{
			glm::vec3 _fighterPosition = m_meshes[1]->GetPosition();
			_fighterPosition.z += (dir.y * 0.5f * dt);
			m_meshes[1]->SetPosition(_fighterPosition);
		}

		//Rotate
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Rotate)
		{
			glm::vec3 _fighterRotation = m_meshes[1]->GetRotation();
			_fighterRotation.z += (dir.y * 3.0f * dt);
			m_meshes[1]->SetRotation(_fighterRotation);
		}

		//Scale
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Scale)
		{
			glm::vec3 _fighterScale = m_meshes[1]->GetScale();
			_fighterScale.z += (dir.y * 0.0001f * dt);
			m_meshes[1]->SetScale(_fighterScale);
		}
	}

	if (OpenGLTechniques::ToolWindow::ResetTransform)
	{
		m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
		m_meshes[1]->SetRotation({ 0.0f, 0.0f, 0.0f });
		m_meshes[1]->SetScale({ 0.0008f, 0.0008f, 0.0008f });
		OpenGLTechniques::ToolWindow::ResetTransform = false;
	}
}