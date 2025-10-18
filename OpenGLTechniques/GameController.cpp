#include "GameController.h"
#include "ToolWindow.h"
#include "Application.h"
#include "MoveLightScene.h"
#include "TransformScene.h"
#include "WaterScene.h"
#include "SpaceScene.h"

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = {};
	m_shaderSkybox = {};
	m_camera = {};
	m_meshLight = {};
	m_meshBoxes.clear();
	m_currentScene = {};
}

GameController::~GameController()
{
	delete m_currentScene;
	m_scenes.clear();
}

void GameController::Initialize(Resolution _resolution, glm::vec2 _windowSize)
{

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	srand((unsigned int)time(0));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);

#pragma region LoadAssets
	{
		m_shaderColor = Shader();
		m_shaderColor.LoadShaders("./Debug/shaders/Color.vert", "./Debug/shaders/Color.frag");

		m_shaderDiffuse = Shader();
		m_shaderDiffuse.LoadShaders("./Debug/shaders/Diffuse.vert", "./Debug/shaders/Diffuse.frag");

		m_shaderWorldDiffuse = Shader();
		m_shaderWorldDiffuse.LoadShaders("./Debug/shaders/Diffuse.vert", "./Debug/shaders/DiffuseWorld.frag");

		m_shaderFont = Shader();
		m_shaderFont.LoadShaders("./Debug/shaders/Font.vert", "./Debug/shaders/Font.frag");

		m_shaderSkybox = Shader();
		m_shaderSkybox.LoadShaders("./Debug/shaders/Skybox.vert", "./Debug/shaders/Skybox.frag");

		m_shaderPost = Shader();
		m_shaderPost.LoadShaders("./Debug/shaders/PostProcessing.vert", "./Debug/shaders/PostProcessing.frag");

		Mesh *light = new Mesh();
		light->Create(&m_shaderColor, "./Debug/Assets/Models/dcube.obj", 1, true);
		Mesh::Lights.push_back(light);
		m_meshBoxes.push_back(light);

		Mesh *fighter = new Mesh();
		fighter->Create(&m_shaderDiffuse, "./Debug/Assets/Models/fnew.obj", 1, true);
		m_meshBoxes.push_back(fighter);

		Mesh *fish = new Mesh();
		fish->Create(&m_shaderDiffuse, "./Debug/Assets/Models/Fish.obj");
		m_meshBoxes.push_back(fish);

		Mesh *asteroids = new Mesh();
		asteroids->Create(&m_shaderDiffuse, "./Debug/Assets/Models/asteroid.obj", 100);
		m_meshBoxes.push_back(asteroids);

		m_postProcessor = PostProcessor();
		m_postProcessor.Create(&m_shaderPost);

		m_skybox = Skybox();
		m_skybox.Create(&m_shaderSkybox, "./Debug/Assets/Models/Skybox.obj",
						{
							"./Debug/Assets/Textures/Skybox/right.jpg",
							"./Debug/Assets/Textures/Skybox/left.jpg",
							"./Debug/Assets/Textures/Skybox/top.jpg",
							"./Debug/Assets/Textures/Skybox/bottom.jpg",
							"./Debug/Assets/Textures/Skybox/front.jpg",
							"./Debug/Assets/Textures/Skybox/back.jpg",
						});

		Fonts f = Fonts();
		f.Create(&m_shaderFont, "./Debug/Assets/Fonts/arial.ttf", 100);

		for (int i = 0; i < 7; i++)
		{
			m_fonts.push_back(f);
		}
	}

#pragma endregion

#pragma region CreateScenes
	{
		MoveLightScene *moveLightScene = new MoveLightScene(m_camera);
		moveLightScene->AddMesh(m_meshBoxes[0]);
		moveLightScene->AddMesh(m_meshBoxes[1]);
		moveLightScene->Init();
		m_scenes.push_back(moveLightScene);

		TransformScene *transformScene = new TransformScene(m_camera);
		transformScene->AddMesh(m_meshBoxes[0]);
		transformScene->AddMesh(m_meshBoxes[1]);
		m_scenes.push_back(transformScene);

		WaterScene *waterScene = new WaterScene(m_camera);
		waterScene->AddMesh(m_meshBoxes[0]);
		waterScene->AddMesh(m_meshBoxes[2]);
		waterScene->AddShader(&m_shaderDiffuse);
		waterScene->SetPostProcessor(m_postProcessor);
		m_scenes.push_back(waterScene);

		SpaceScene *spaceScene = new SpaceScene(m_camera);
		spaceScene->AddMesh(m_meshBoxes[0]);
		spaceScene->AddMesh(m_meshBoxes[1]);
		spaceScene->AddMesh(m_meshBoxes[3]);
		spaceScene->AddShader(&m_shaderDiffuse);
		spaceScene->SetSkybox(m_skybox);
		m_scenes.push_back(spaceScene);

		m_currentScene = m_scenes[0];
		m_currentSceneNum = 0;
	}
#pragma endregion

	OpenGLTechniques::ToolWindow ^ window = gcnew OpenGLTechniques::ToolWindow();
	window->Show();
}

void GameController::ProcessInput(float _dt)
{
	int nextScene = (int)OpenGLTechniques::ToolWindow::game_mode;
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_currentScene->Render();

	std::stringstream fps_MSG;
	std::stringstream mousePosition_MSG;
	std::stringstream mouseLeftDown_MSG;
	std::stringstream mouseMiddleDown_MSG;
	std::stringstream position_MSG;
	std::stringstream rotation_MSG;
	std::stringstream scale_MSG;

	fps_MSG << "FPS " << Utilities::FPSCounter::FPS;
	mousePosition_MSG << "Mouse Position " << Application::Mouse.GetPosition().x << " " << Application::Mouse.GetPosition().y;

	if (Application::Mouse.GetMouseDown())
	{
		mouseLeftDown_MSG << "Left Buttom: Down";
	}
	else
	{
		mouseLeftDown_MSG << "Left Buttom: Up";
	}

	if (Application::Mouse.GetMouseMiddleDown())
	{
		mouseMiddleDown_MSG << "Middle Buttom: Down";
	}
	else
	{
		mouseMiddleDown_MSG << "Middle Buttom: Up";
	}

	if (m_currentSceneNum == 2)
	{
		position_MSG << "Fish Position " << glm::to_string(m_meshBoxes[2]->GetPosition());
		rotation_MSG << "Fish Rotation " << glm::to_string(m_meshBoxes[2]->GetRotation());
		scale_MSG << "Fish Scale " << glm::to_string(m_meshBoxes[2]->GetScale());
	}
	else
	{
		position_MSG << "Fighter Position " << glm::to_string(m_meshBoxes[1]->GetPosition());
		rotation_MSG << "Fighter Rotation " << glm::to_string(m_meshBoxes[1]->GetRotation());
		scale_MSG << "Fighter Scale " << glm::to_string(m_meshBoxes[1]->GetScale());
	}

	glm::vec3 textCol = glm::vec3(1.0f, 1.0f, 0.0f);
	m_fonts[0].RenderText(fps_MSG.str(), 10, 20, 0.2f, textCol);
	m_fonts[1].RenderText(mousePosition_MSG.str(), 10, 40, 0.2f, textCol);
	m_fonts[2].RenderText(mouseLeftDown_MSG.str(), 10, 60, 0.2f, textCol);
	m_fonts[3].RenderText(mouseMiddleDown_MSG.str(), 10, 80, 0.2f, textCol);
	m_fonts[4].RenderText(position_MSG.str(), 10, 100, 0.2f, textCol);
	m_fonts[5].RenderText(rotation_MSG.str(), 10, 120, 0.2f, textCol);
	m_fonts[6].RenderText(scale_MSG.str(), 10, 140, 0.2f, textCol);
}

void GameController::CleanUp()
{
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count]->CleanUp();
	}

	m_shaderDiffuse.CleanUp();
	m_shaderWorldDiffuse.CleanUp();
	m_shaderColor.CleanUp();
	m_shaderFont.CleanUp();
}