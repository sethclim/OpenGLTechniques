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
	m_meshes[0]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[0]->SetScale({ 0.002f, 0.002f, 0.002f });
	m_meshes[0]->SetPosition({ 0.0f, 0.0f, 0.0f });
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
			glm::vec3 _fighterPosition = m_meshes[0]->GetPosition();
			_fighterPosition += (dir * 0.5f * dt);
			m_meshes[0]->SetPosition(_fighterPosition);
		}
		
		//Rotate
 		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Rotate)
		{
			glm::vec3 _fighterRotation = m_meshes[0]->GetRotation();
			_fighterRotation += (dir * 3.0f * dt);
			m_meshes[0]->SetRotation(_fighterRotation);
		}

		//Scale
		if (OpenGLTechniques::ToolWindow::SceneTwoOptions::Scale)
		{
			glm::vec3 _fighterScale = m_meshes[0]->GetScale();
			_fighterScale += (dir * 0.02f * dt);
			m_meshes[0]->SetScale(_fighterScale);
		}

		//m_meshes[0]->SetPosition(_curLightPos);
		//m_meshes[0]->SetRotation(_curLightPos);
		//m_meshes[1]->SetLightPosition(_curLightPos);
	}

	//if (OpenGLTechniques::ToolWindow::)
	//{
	//	m_meshes[0]->SetPosition({ 0.0f, 0.0f, 0.0f });
	//	OpenGLTechniques::ToolWindow::ResetLight = false;
	//}
}