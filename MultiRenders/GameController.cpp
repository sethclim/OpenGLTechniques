#include "GameController.h"
#include "ToolWindow.h"
#include "Application.h"
#include "SceneOne.h"


GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshLight = { };
	m_meshBoxes.clear();
	//m_currentScene = { };
}

GameController::~GameController()
{

}

void GameController::Initialize(Resolution _resolution, glm::vec2 _windowSize)
{

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	m_camera = Camera(_resolution);
	m_windowSize = _windowSize;

	//Load Assets
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vert", "Color.frag");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vert", "DiffuseWorld.frag");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vert", "Font.frag");

	Mesh* light = new Mesh();

	light->Create(&m_shaderColor, "../Assets/Models/sphere.obj");
	light->SetPosition({ 1.0f, 0.0f, 1.0f });
	light->SetColor({ 3.0f, 1.0f,2.0f });
	light->SetScale({ 0.005f, 0.005f, 0.005f });

	Mesh::Lights.push_back(*light);

	m_meshBoxes.push_back(light);

	Mesh* teapot = new Mesh();

	teapot->Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
	teapot->SetCameraPosition(m_camera.GetPosition());
	teapot->SetScale({ 0.05f, 0.05f, 0.05f });
	teapot->SetPosition({ 0.0f, 0.0f, 0.0f });
	teapot->SetSpecularStrength(8.0f);

	m_meshBoxes.push_back(teapot);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	m_fonts.push_back(f);
	m_fonts.push_back(f);
	m_fonts.push_back(f);

	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();

	SceneOne* sceneOne = new SceneOne(m_camera);
	sceneOne->AddMesh(m_meshBoxes[0]);
	sceneOne->AddMesh(m_meshBoxes[1]);

	m_scenes.push_back(sceneOne);

	m_currentScene = m_scenes[0];


	//std::function<void()> x = [this]()->void
	//{
	//	m_meshBoxes[0].SetPosition({ 0,0,0 });
	//};

	//window->AddCallBack((MultiRenders::ToolWindow::ANSWERCB)x);

}

void GameController::ProcessInput(float _dt)
{
	//glm::vec2 pos = Application::Mouse.GetPosition();

	//float halfX = m_windowSize.x / 2;
	//float halfy = m_windowSize.y / 2;

	m_currentScene = m_scenes[(int)MultiRenders::ToolWindow::Mode::SceneOne];

	if (Application::Mouse.GetMouseDown())
	{
		//glm::vec3 dir = Utilities::ViewToWorldCoordTransform(Application::Mouse.GetPosition(), m_camera);


		//switch (MultiRenders::ToolWindow::game_mode)
		//{
		//case MultiRenders::ToolWindow::Mode::SceneOne:

		//	//glm::vec3 _curLightPos = m_meshBoxes[0].GetPosition();
		//	//_curLightPos += (dir * 0.5f * _dt);

		//	//m_meshBoxes[0].SetPosition(_curLightPos);
		//	//m_meshBoxes[1].SetLightPosition(_curLightPos);
		//	break;

		//case MultiRenders::ToolWindow::Mode::SceneTwo:
		//	//glm::vec3 _curTeaPotPos = m_meshBoxes[1].GetPosition();
		//	//_curTeaPotPos += (dir * 0.5f * _dt);

		//	//m_meshBoxes[1].SetPosition(_curTeaPotPos);
		//	break;
		//}


	}

	m_currentScene->ProcessInput(_dt);
}

void GameController::Update(float dt)
{
	m_meshBoxes[0]->SetSpecularStrength(MultiRenders::ToolWindow::specularStrength);

	Mesh::Lights[0].SetColor({
		MultiRenders::ToolWindow::color_R,
		MultiRenders::ToolWindow::color_G,
		MultiRenders::ToolWindow::color_B
	});
}

void GameController::Render()
{
	//for (unsigned int meshCount = 0; meshCount < m_meshBoxes.size(); meshCount++)
	//{
	//	m_meshBoxes[meshCount].Render(m_camera.GetProjection() * m_camera.GetView());
	//}

	////for (unsigned int fontCount = 0; fontCount < m_fonts.size(); fontCount++)
	////{
	//std::stringstream   mousePosition_MSG;
	//mousePosition_MSG << Application::Mouse.GetPosition().x << " " << Application::Mouse.GetPosition().y;

	//std::stringstream   mouseWorldPosition_MSG;
	//glm::vec3 worldMouse = viewToWorldCoordTransform(Application::Mouse.GetPosition());

	//mouseWorldPosition_MSG << worldMouse.x << " " << worldMouse.y;

	//std::stringstream   fps_MSG;
	//fps_MSG << Utilities::FPSCounter::FPS;

	//m_fonts[0].RenderText(mousePosition_MSG.str(), 10, 20, 0.2f, {1.0f, 1.0f, 1.0f});
	//m_fonts[1].RenderText(mouseWorldPosition_MSG.str(), 10, 50, 0.2f, { 1.0f, 1.0f, 0.0f });
	//m_fonts[2].RenderText(fps_MSG.str(), 10, 80, 0.2f, { 1.0f, 1.0f, 0.0f });
	////}

	m_currentScene->Render();

}

void GameController::CleanUp()
{
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count]->CleanUp();
	}

	m_shaderDiffuse.CleanUp();
	m_shaderColor.CleanUp();
}



