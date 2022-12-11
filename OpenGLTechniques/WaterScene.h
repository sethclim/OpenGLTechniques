#ifndef WaterScene_H
#define WaterScene_H

#include "Scene.h"

class WaterScene : public Scene
{
public:
	WaterScene();
	WaterScene(Camera _camera);
	virtual ~WaterScene();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

	int GetNumberOfBoxes() { return boxes.size(); }

private:
	std::vector<Mesh *> boxes;
};

#endif // !WaterScene_H