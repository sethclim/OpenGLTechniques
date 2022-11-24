#include "GameController.h"
#include "ToolWindow.h"
#include "Application.h"


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
	m_windowSize = _windowSize;

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
	teapot.SetPosition({ 0.0f, 0.0f, -2.0f });
	teapot.SetSpecularStrength(8.0f);

	m_meshBoxes.push_back(teapot);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	m_fonts.push_back(f);
	m_fonts.push_back(f);
	m_fonts.push_back(f);

	MultiRenders::ToolWindow^ window = gcnew MultiRenders::ToolWindow();
	window->Show();


	std::function<void()> x = [this]()->void
	{
		m_meshBoxes[0].SetPosition({ 0,0,0 });
	};

	//window->AddCallBack((MultiRenders::ToolWindow::ANSWERCB)x);

}



void GameController::ProcessInput(float _dt)
{
	glm::vec2 pos = Application::Mouse.GetPosition();

	float halfX = m_windowSize.x / 2;
	float halfy = m_windowSize.y / 2;

	//m_meshBoxes[0].SetPosition(glm::vec3(1, 0, 0));

	//glm::vec3 g = viewToWorldCoordTransform(Application::Mouse.GetPosition());
	////g.z = 0;
	//m_meshBoxes[0].SetPosition(g);
	//m_meshBoxes[1].SetLightPosition(g);


	if (Application::Mouse.GetMouseDown())
	{
		glm::vec3 dir = viewToWorldCoordTransform(Application::Mouse.GetPosition());
		glm::vec3 _curPos = m_meshBoxes[0].GetPosition();
		_curPos += (dir * 0.5f * _dt);

		m_meshBoxes[0].SetPosition(_curPos);
		m_meshBoxes[0].SetLightPosition(_curPos);

	}
}

glm::vec3 GameController::viewToWorldCoordTransform(glm::vec2 _mouse) {

	float x = 2.0 * _mouse.x / WindowController::GetInstance().GetResolution().m_width - 1;
	float y = 2.0 * _mouse.y / WindowController::GetInstance().GetResolution().m_height - 1;

	glm::vec3 cam_fwd = glm::normalize(glm::vec3(0) - m_camera.GetPosition());
	glm::vec3 cam_to_light = glm::vec3(0.0f, 0.0f, 0.0f) - m_camera.GetPosition();

	float diff = 1000.0 - 0.1;

	float eye_hit_z = -glm::length(cam_to_light) * glm::dot(cam_fwd, glm::normalize(cam_to_light));

	float ndc_depth = ((1000.0 + 0.1) + (2.0 * 1000.0 * 0.1) / eye_hit_z) / (1000.0 - 0.1);

	glm::mat4 ProjectView = m_camera.GetProjection() * m_camera.GetView();
	glm::mat4 viewProjectionInverse = glm::inverse(ProjectView);

	glm::vec4 screenPos = glm::vec4(x, -y, ndc_depth, 1.0f);
	glm::vec4 worldPos = viewProjectionInverse * screenPos;

	worldPos.w = 1 / worldPos.w;
	worldPos.y *= worldPos.w;
	worldPos.x *= worldPos.w;
	worldPos.z *= worldPos.w;

	return glm::vec3(worldPos);
}


glm::vec3 GameController::MoveToQuadCenter(glm::vec3 _center, glm::vec3 _curPos, float _dt)
{
	glm::vec3 screenCentre = glm::vec3(0, 0, 0);

	//Log("Quad Center");
	//Log(glm::to_string(_center));
	//Log("Centre");
	//Log(glm::to_string(screenCentre));
	

	glm::vec3 dir = glm::normalize(_center - _curPos);
	//Log("Dir");
	//Log(glm::to_string(dir));

	//GetPosition() += direction * speed * _deltatime
	return _curPos += (glm::vec3(dir.x, -dir.y, 0) * 0.5f * _dt);
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

	//for (unsigned int fontCount = 0; fontCount < m_fonts.size(); fontCount++)
	//{
	std::stringstream   mousePosition_MSG;
	mousePosition_MSG << Application::Mouse.GetPosition().x << " " << Application::Mouse.GetPosition().y;

	std::stringstream   mouseWorldPosition_MSG;
	glm::vec3 worldMouse = viewToWorldCoordTransform(Application::Mouse.GetPosition());

	mouseWorldPosition_MSG << worldMouse.x << " " << worldMouse.y;

	//std::stringstream   fps_MSG;
	//glm::vec3 worldMouse = viewToWorldCoordTransform(Application::Mouse.GetPosition());

	m_fonts[0].RenderText(mousePosition_MSG.str(), 10, 20, 0.2f, {1.0f, 1.0f, 1.0f});
	m_fonts[1].RenderText(mouseWorldPosition_MSG.str(), 10, 50, 0.2f, { 1.0f, 1.0f, 0.0f });
		//m_fonts[2].RenderText(fps_MSG.str(), 10, 80, 0.2f, { 1.0f, 1.0f, 0.0f });
	//}

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



