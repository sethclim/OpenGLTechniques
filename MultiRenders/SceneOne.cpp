#include "SceneOne.h"

SceneOne::SceneOne(Camera _camera)
{
	m_camera = _camera;
}

SceneOne::~SceneOne()
{

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
}