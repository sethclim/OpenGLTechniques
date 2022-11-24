#ifndef APPLICATION_H
#define APPLICATION_H

#include "StandardIncludes.h"
#include "WindowController.h"
#include "GameController.h"
#include "Mouse.h"
#include "Utilities.h"

class Application :public Singleton<Application>
{
public:
	Application();
	virtual ~Application();

	void Run();
	void Cursor_Position_Callback(double xpos, double ypos);

	static Mouse Mouse;
private:
	static void glfw_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos);
	static void glfw_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);

	float m_LastFrameTime;
	GameController* m_gameController;
};

#endif // !APPLICATION_H


