#include "Application.h"

Application::Application(): m_gameController( new GameController() )
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // call this first to create window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW"); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key

	m_gameController->Initialize(WindowController::GetInstance().GetResolution(), WindowController::GetInstance().GetSize());
}

Application::~Application()
{
}

void Application::Initialize()
{
}

void Application::Run()
{
	double t = 0.0;
	double dt = 1 / 60.0;

	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0)
	{
		System::Windows::Forms::Application::DoEvents(); //Handle CLI Form Events

		//PROCESS INPUT
		//TODO

		double newTime = glfwGetTime();
		double frameTime = newTime - m_LastFrameTime;
		m_LastFrameTime = newTime;

		while (frameTime > 0.0)
		{
			float deltaTime = std::min(frameTime, dt);

			//Update
			m_gameController->Update(deltaTime);

			frameTime -= deltaTime;
			t += deltaTime;
		}

		//RENDER
		m_gameController->Render();

		//m_meshBoxes[0].SetSpecularStrength(MultiRenders::ToolWindow::specularStrength);

		//Mesh::Lights[0].SetColor({
		//	MultiRenders::ToolWindow::color_R,
		//	MultiRenders::ToolWindow::color_G,
		//	MultiRenders::ToolWindow::color_B
		//	});

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		//{
		//	Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		//}

		//for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		//{
		//	m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		//}

		//f.RenderText("Testing Text", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });


		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	}

	m_gameController->CleanUp();
}
