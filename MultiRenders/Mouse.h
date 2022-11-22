#ifndef MOUSE_H
#define MOUSE_H

#include "StandardIncludes.h"

struct Mouse
{
public:
	Mouse()
	{
		m_pos = glm::vec2();
	}
	glm::vec2 GetPosition() { return m_pos; }
	void SetPosition(double xpos, double ypos) 
	{ 
		m_pos.x = xpos;
		m_pos.y = ypos;
	}
private:
	glm::vec2 m_pos;
};

#endif // !MOUSE_H

