#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
//#include "WindowController.h"
#include "Camera.h"
#include "Fonts.h"
#include "Mouse.h"
#include "Skybox.h"
#include "PostProcessor.h"

class Scene;


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
	

private:
	Shader     m_shaderColor;
	Shader     m_shaderDiffuse;
	Shader     m_shaderFont;
	Shader	   m_shaderWorldDiffuse;
	Shader     m_shaderSkybox;
	Shader     m_shaderPost;

	Camera     m_camera;
	Mesh       m_meshLight;
	Scene*     m_currentScene;
	int		   m_currentSceneNum;

	glm::vec2 m_windowSize;
	std::vector<Mesh*>    m_meshBoxes;
	std::vector<Fonts>   m_fonts;
	PostProcessor m_postProcessor;
	Skybox m_skybox;
	GLuint vao;

	std::vector<Scene*>   m_scenes;
};

#endif // !GAMECONTROLLER_H


