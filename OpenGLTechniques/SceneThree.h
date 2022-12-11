#ifndef SceneThree_H
#define SceneThree_H

#include "Scene.h"

class SceneThree : public Scene
{
public:
	SceneThree();
	SceneThree(Camera _camera);
	virtual ~SceneThree();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	int GetNumberOfBoxes() { return boxes.size(); }

private:
	std::vector<Mesh *> boxes;
};

#endif // !SCENETHREE_H