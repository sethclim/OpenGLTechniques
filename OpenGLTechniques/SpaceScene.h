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

private:
	std::vector<Mesh*> boxes;
};

#endif // !SPACESCENE_H