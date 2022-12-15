#include "GameController.h"
#include "ToolWindow.h"
#include "Application.h"
#include "MoveLightScene.h"
#include "TransformScene.h"
#include "WaterScene.h"
#include "SpaceScene.h"

GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderSkybox = { };
	m_camera = { };
	m_meshLight = { };
	m_meshBoxes.clear();
	m_currentScene = { };
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
	//glCullFace(GL_FRONT);
	srand((unsigned int)time(0));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);

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

		m_shaderSkybox = Shader();
		m_shaderSkybox.LoadShaders("Skybox.vert", "Skybox.frag");

		m_shaderPost = Shader();
		m_shaderPost.LoadShaders("PostProcessing.vert", "PostProcessing.frag");

		Mesh* light = new Mesh();
		light->Create(&m_shaderColor, "../Assets/Models/sphere.obj");
		Mesh::Lights.push_back(light);
		m_meshBoxes.push_back(light);

		Mesh* fighter = new Mesh();
		fighter->Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
		m_meshBoxes.push_back(fighter);

		Mesh* fish = new Mesh();
		fish->Create(&m_shaderDiffuse, "../Assets/Models/Fish.obj");
		m_meshBoxes.push_back(fish);

		m_postProcessor = PostProcessor();
		m_postProcessor.Create(&m_shaderPost);

		m_skybox = Skybox();
		m_skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj",
			{
				"../Assets/Textures/Skybox/right.jpg",
				"../Assets/Textures/Skybox/left.jpg",
				"../Assets/Textures/Skybox/top.jpg",
				"../Assets/Textures/Skybox/bottom.jpg",
				"../Assets/Textures/Skybox/front.jpg",
				"../Assets/Textures/Skybox/back.jpg",
			}
		);

		Fonts f = Fonts();
		f.Create(&m_shaderFont, "arial.ttf", 100);

		for (int i = 0; i < 7; i++)
		{
			m_fonts.push_back(f);
		}
	}

#pragma endregion

#pragma region CreateScenes
	{
		MoveLightScene* moveLightScene = new MoveLightScene(m_camera);
		moveLightScene->AddMesh(m_meshBoxes[0]);
		moveLightScene->AddMesh(m_meshBoxes[1]);
		moveLightScene->Init();
		m_scenes.push_back(moveLightScene);

		TransformScene* transformScene = new TransformScene(m_camera);
		transformScene->AddMesh(m_meshBoxes[0]);
		transformScene->AddMesh(m_meshBoxes[1]);
		m_scenes.push_back(transformScene);

		WaterScene* waterScene = new WaterScene(m_camera);
		waterScene->AddMesh(m_meshBoxes[0]);
		waterScene->AddMesh(m_meshBoxes[2]);
		waterScene->AddShader(&m_shaderDiffuse);
		waterScene->SetPostProcessor(m_postProcessor);
		m_scenes.push_back(waterScene);

		SpaceScene* spaceScene = new SpaceScene(m_camera);
		spaceScene->AddMesh(m_meshBoxes[0]);
		spaceScene->AddMesh(m_meshBoxes[1]);
		spaceScene->AddShader(&m_shaderDiffuse);
		spaceScene->SetSkybox(m_skybox);
		m_scenes.push_back(spaceScene);

		m_currentScene = m_scenes[0];
		m_currentSceneNum = 0;
	}
#pragma endregion

	OpenGLTechniques::ToolWindow^ window = gcnew OpenGLTechniques::ToolWindow();
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

	m_currentScene->Render();

	std::stringstream   mousePosition_MSG;
	mousePosition_MSG << "Mouse Position " << Application::Mouse.GetPosition().x << " " << Application::Mouse.GetPosition().y;
	std::stringstream   fps_MSG;
	fps_MSG << "FPS " << Utilities::FPSCounter::FPS;

	std::stringstream   position_MSG;
	std::stringstream   rotation_MSG;
	std::stringstream   scale_MSG;

	//WaterScene* s = dynamic_cast<WaterScene*>(m_scenes[2]);
	position_MSG << "Position " << glm::to_string(m_meshBoxes[2]->GetPosition());
	rotation_MSG << "Rotation " << glm::to_string(m_meshBoxes[2]->GetRotation());
	scale_MSG << "Scale "    << glm::to_string(m_meshBoxes[2]->GetScale());

	glm::vec3 textCol = glm::vec3(1.0f, 1.0f, 0.0f);

	m_fonts[0].RenderText(fps_MSG.str(), 10, 20, 0.2f, textCol);
	m_fonts[1].RenderText(mousePosition_MSG.str(), 10, 50, 0.2f, textCol);

	m_fonts[4].RenderText(position_MSG.str(), 10, 80,  0.2f, textCol);
	m_fonts[5].RenderText(rotation_MSG.str(), 10, 100, 0.2f, textCol);
	m_fonts[6].RenderText(scale_MSG.str(),    10, 120, 0.2f, textCol);

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