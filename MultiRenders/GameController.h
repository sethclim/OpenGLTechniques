#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
//#include "WindowController.h"
#include "Camera.h"
#include "Fonts.h"
#include "Mouse.h"

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	void Initialize(Resolution _resolution, glm::vec2 _windowSize);

	void ProcessInput(Mouse* mouse);
	void Update(float dt);
	void Render();
	void CleanUp();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Camera m_camera;
	Mesh   m_meshLight;
	Mouse*  m_mouse;

	std::vector<Mesh>    m_meshBoxes;
	std::vector<Fonts>   m_fonts;
};

#endif // !GAMECONTROLLER_H


