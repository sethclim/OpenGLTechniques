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
		m_mouseMiddleDown = false;
	}
	 glm::vec2 GetPosition() { return m_pos; }
	 void SetPosition(double xpos, double ypos) 
	{ 
		m_pos.x = xpos;
		m_pos.y = ypos;
	}

	 bool GetMouseDown() { return m_mouseDown; }
	 void SetMouseDown(bool _down) { m_mouseDown = _down; }

	 bool GetMouseMiddleDown() { return m_mouseMiddleDown; }
	 void SetMouseMiddleDown(bool _down) { m_mouseMiddleDown = _down; }

	 void SetScroll(float _y) { y_offset = _y; }
	 float GetScroll() { return y_offset; }

private:
	 glm::vec2 m_pos;
	 bool m_mouseDown;
	 bool m_mouseMiddleDown;
	 float y_offset;
};

#endif // !MOUSE_H

