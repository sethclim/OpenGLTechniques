#include "GameController.h"
#include "ToolWindow.h"


GameController::GameController()
{
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshLight = { };
	m_meshBoxes.clear();
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

	//Load Assets
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vert", "Color.frag");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vert", "Diffuse.frag");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vert", "Font.frag");

	Mesh light = Mesh();

	light.Create(&m_shaderColor, "../Assets/Models/sphere.obj");
	light.SetPosition({ 1.0f, 0.0f, 0.0f });
	light.SetColor({ 3.0f, 1.0f,2.0f });
	light.SetScale({ 0.005f, 0.005f, 0.005f });

	Mesh::Lights.push_back(light);

	m_meshBoxes.push_back(light);

	Mesh teapot = Mesh();

	teapot.Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.01f, 0.01f, 0.01f });
	teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	teapot.SetSpecularStrength(8.0f);

	m_meshBoxes.push_back(teapot);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	m_fonts.push_back(f);

	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();
}



void GameController::ProcessInput(Mouse* _mouse)
{
	m_mouse = _mouse;
	_mouse->GetPosition();
}

void GameController::Update(float dt)
{
	m_meshBoxes[0].SetSpecularStrength(MultiRenders::ToolWindow::specularStrength);

	Mesh::Lights[0].SetColor({
		MultiRenders::ToolWindow::color_R,
		MultiRenders::ToolWindow::color_G,
		MultiRenders::ToolWindow::color_B
	});
}

void GameController::Render()
{
	for (unsigned int meshCount = 0; meshCount < m_meshBoxes.size(); meshCount++)
	{
		m_meshBoxes[meshCount].Render(m_camera.GetProjection() * m_camera.GetView());
	}

	for (unsigned int fontCount = 0; fontCount < m_fonts.size(); fontCount++)
	{
		std::stringstream   mousePosition_MSG;
		mousePosition_MSG << m_mouse->GetPosition().x << " " << m_mouse->GetPosition().y;

		m_fonts[fontCount].RenderText(mousePosition_MSG.str(), 10, 500, 0.5f, {1.0f, 1.0f, 0.0f});
	}

}

void GameController::CleanUp()
{
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].CleanUp();
	}

	m_shaderDiffuse.CleanUp();
	m_shaderColor.CleanUp();
}
