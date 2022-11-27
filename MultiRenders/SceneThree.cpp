#include "SceneThree.h"

SceneThree::SceneThree(Camera _camera)
{
	m_camera = _camera;
}

SceneThree::~SceneThree()
{

}

void SceneThree::ProcessInput(float dt)
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