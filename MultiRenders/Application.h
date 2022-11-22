#ifndef APPLICATION_H
#define APPLICATION_H

#include "StandardIncludes.h"
#include "WindowController.h"
#include "GameController.h"
#include "Mouse.h"

class Application :public Singleton<Application>
{
public:
	Application();
	virtual ~Application();

	void Run();
	void Cursor_Position_Callback(double xpos, double ypos);

private:
	static void glfw_Cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos);

	float m_LastFrameTime;
	Mouse mouse;
	GameController* m_gameController;
};

#endif // !APPLICATION_H


