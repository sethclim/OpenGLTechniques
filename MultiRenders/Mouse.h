#ifndef MOUSE_H
#define MOUSE_H

#include "StandardIncludes.h"

static class Mouse
{
public:
	Mouse()
	{
		m_pos = glm::vec2();
		m_mouseDown = false;
	}
	 glm::vec2 GetPosition() { return m_pos; }
	 void SetPosition(double xpos, double ypos) 
	{ 
		m_pos.x = xpos;
		m_pos.y = ypos;
	}

	 bool GetMouseDown() { return m_mouseDown; }
	 void SetMouseDown(bool _down) { m_mouseDown = _down; }

private:
	 glm::vec2 m_pos;
	 bool m_mouseDown;
};

#endif // !MOUSE_H

