#ifndef SPACESCENE_H
#define SPACESCENE_H

#include "Scene.h"

class SpaceScene : public Scene
{
public:
	SpaceScene();
	SpaceScene(Camera _camera);
	virtual ~SpaceScene();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	int GetNumberOfBoxes() { return boxes.size(); }

	void SetSkybox(Skybox& _skybox) { m_skybox = _skybox;  }

private:
	std::vector<Mesh*> boxes;
	Skybox m_skybox;
};

#endif // !SPACESCENE_H