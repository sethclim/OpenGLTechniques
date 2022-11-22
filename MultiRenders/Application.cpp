#include "Application.h"

Application::Application(): m_gameController( new GameController() ), mouse(Mouse())
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // call this first to create window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW"); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glfwSetCursorPosCallback(window, &glfw_Cursor_Position_Callback);

	m_gameController->Initialize(WindowController::GetInstance().GetResolution(), WindowController::GetInstance().GetSize());
}

Application::~Application()
{
	delete m_gameController;
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

			m_gameController->ProcessInput(&mouse);

			//Update
			m_gameController->Update(deltaTime);

			frameTime -= deltaTime;
			t += deltaTime;
		}

		//RENDER
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_gameController->Render();

		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	}

	m_gameController->CleanUp();
}

void Application::Cursor_Position_Callback(double xpos, double ypos)
{
	mouse.SetPosition(xpos, ypos);
}

void Application::glfw_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos)
{
	Application::GetInstance().Cursor_Position_Callback(xpos, ypos);
}
