#include "WaterScene.h"
#include "ToolWindow.h"

WaterScene::WaterScene(Camera _camera)
{
	m_camera = _camera;
	time = 0.0f;
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
	m_meshes[0]->SetLightSpecularColor({ 1.0f, 1.0f,1.0f });

	m_meshes[1]->SetCameraPosition(m_camera.GetPosition());
	m_meshes[1]->SetScale({ 0.02f, 0.02f, 0.02f }); 
	m_meshes[1]->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes[1]->SetRotation({ 0,180,0 });
	m_meshes[1]->SetSpecularStrength(1);
}

void WaterScene::ProcessInput(float dt)
{
	Shader* postShader = m_postProcessor.GetShader();

	glUseProgram(postShader->GetProgramID());

	if (OpenGLTechniques::ToolWindow::Scene_Three_Options == OpenGLTechniques::ToolWindow::SceneThreeOptions::BlueTint)
	{
		postShader->SetInt("blue", 1);
	}
	else
	{
		postShader->SetInt("blue",  0);
	}

	postShader->SetFloat("freq", OpenGLTechniques::ToolWindow::SceneThreeValues::Frequency);
	postShader->SetFloat("amplitude", OpenGLTechniques::ToolWindow::SceneThreeValues::Amplitude);

	time += 0.004f;
	postShader->SetFloat("time", time);

	glUseProgram(0);
}

void WaterScene::Update(float dt)
{

}

void WaterScene::Render()
{
	m_postProcessor.Start();

	Scene::Render();

	m_postProcessor.End();
}	