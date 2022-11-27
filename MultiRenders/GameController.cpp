#include "GameController.h"
#include "ToolWindow.h"
#include "Application.h"
#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"


GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshLight = { };
	m_meshBoxes.clear();
	m_currentScene = { };
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

#pragma region LoadAssets
	{
		m_shaderColor = Shader();
		m_shaderColor.LoadShaders("Color.vert", "Color.frag");

		m_shaderDiffuse = Shader();
		m_shaderDiffuse.LoadShaders("Diffuse.vert", "Diffuse.frag");

		m_shaderWorldDiffuse = Shader();
		m_shaderWorldDiffuse.LoadShaders("Diffuse.vert", "DiffuseWorld.frag");

		m_shaderFont = Shader();
		m_shaderFont.LoadShaders("Font.vert", "Font.frag");

		Mesh* light = new Mesh();
		light->Create(&m_shaderColor, "../Assets/Models/sphere.obj");
		Mesh::Lights.push_back(light);
		m_meshBoxes.push_back(light);

		Mesh* teapot = new Mesh();
		teapot->Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
		m_meshBoxes.push_back(teapot);

		Mesh* teapot2 = new Mesh();
		teapot2->Create(&m_shaderWorldDiffuse, "../Assets/Models/teapot.obj");
		m_meshBoxes.push_back(teapot2);

		Mesh* sphereHappy = new Mesh();
		sphereHappy->Create(&m_shaderDiffuse, "../Assets/Models/sphere.obj");
		m_meshBoxes.push_back(sphereHappy);

		//Mesh* box = new Mesh();
		//box->Create(&m_shaderWorldDiffuse, "../Assets/Models/cube.obj");
		//m_meshBoxes.push_back(box);
		

		Fonts f = Fonts();
		f.Create(&m_shaderFont, "arial.ttf", 100);

		m_fonts.push_back(f);
		m_fonts.push_back(f);
		m_fonts.push_back(f);
	}

#pragma endregion

#pragma region CreateScenes
	{
		SceneOne* sceneOne = new SceneOne(m_camera);
		sceneOne->AddMesh(m_meshBoxes[0]);
		sceneOne->AddMesh(m_meshBoxes[1]);
		sceneOne->Init();

		m_scenes.push_back(sceneOne);

		SceneTwo* sceneTwo = new SceneTwo(m_camera);
		sceneTwo->AddMesh(m_meshBoxes[2]);
		//sceneTwo->Init();

		m_scenes.push_back(sceneTwo);

		SceneThree* sceneThree = new SceneThree(m_camera);
		sceneThree->AddMesh(m_meshBoxes[0]);
		sceneThree->AddMesh(m_meshBoxes[3]);
		sceneThree->AddShader(&m_shaderDiffuse);
		//sceneThree->Init();

		m_scenes.push_back(sceneThree);

		m_currentScene = m_scenes[0];
		m_currentSceneNum = 0;
	}
#pragma endregion

	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();
}

void GameController::ProcessInput(float _dt)
{
	int nextScene = (int)MultiRenders::ToolWindow::game_mode;
	if (nextScene != m_currentSceneNum)
	{
		m_currentScene = m_scenes[nextScene];
		m_currentScene->Init();
		m_currentSceneNum = nextScene;
	}

	m_currentScene->ProcessInput(_dt);
}

void GameController::Update(float dt)
{
	m_currentScene->Update(dt);
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



