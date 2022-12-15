#include "Application.h"

Mouse Application::Mouse;

Application::Application(): m_gameController( new GameController() )
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // call this first to create window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW"); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key


	glfwSetCursorPosCallback(window, &glfw_Cursor_Position_Callback);
	glfwSetMouseButtonCallback(window, &glfw_Mouse_Button_Callback);
	glfwSetScrollCallback(window, &glfw_Scroll_Callback);

	m_gameController->Initialize(WindowController::GetInstance().GetResolution(), WindowController::GetInstance().GetSize());

	glfwSwapInterval(0);
}

Application::~Application()
{
	delete m_gameController;
}

void Application::Run()
{
	double t = 0.0;

	const double fpsLimit = 1.0 / 60.0;

	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0)
	{
		System::Windows::Forms::Application::DoEvents(); //Handle CLI Form Events

		//PROCESS INPUT
		double newTime = glfwGetTime();
		double frameTime = newTime - m_LastFrameTime;
		m_LastFrameTime = newTime;

		float deltaTime = std::min(frameTime, fpsLimit);

		m_gameController->ProcessInput(deltaTime);
		m_gameController->Update(deltaTime);

		Utilities::FPSCounter::CalculateFrameRate();

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
	Mouse.SetPosition(xpos, ypos);
}

void Application::glfw_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos)
{
	Application::GetInstance().Cursor_Position_Callback(xpos, ypos);
}

void Application::glfw_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Mouse.SetMouseDown(true);
	}
	else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		Mouse.SetMouseDown(false);
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		Mouse.SetMouseMiddleDown(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		Mouse.SetMouseMiddleDown(false);
	}

}

void Application::glfw_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse.SetScroll(yoffset);
}