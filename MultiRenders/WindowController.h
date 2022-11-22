#ifndef WINDOWCONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardIncludes.h"

class WindowController : public Singleton<WindowController>
{
public:
	WindowController();
	virtual ~WindowController();

	GLFWwindow* GetWindow() { if (m_Window == nullptr) { NewWindow(); } return m_Window; }


	void NewWindow();
	Resolution GetResolution();
	glm::vec2 GetSize();

private:
	GLFWwindow* m_Window;
};

#endif // WindowController_H