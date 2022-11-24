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

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void CleanUp();
	

	//void Test();

private:
	glm::vec3 MoveToQuadCenter(glm::vec3 _center, glm::vec3 _curPos, float _dt);
	glm::vec3 viewToWorldCoordTransform(glm::vec2 _mouse);


	Shader    m_shaderColor;
	Shader    m_shaderDiffuse;
	Shader    m_shaderFont;
	Camera    m_camera;
	Mesh      m_meshLight;

	glm::vec2 m_windowSize;
	std::vector<Mesh>    m_meshBoxes;
	std::vector<Fonts>   m_fonts;
};

#endif // !GAMECONTROLLER_H


