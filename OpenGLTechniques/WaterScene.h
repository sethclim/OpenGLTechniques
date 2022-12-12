#ifndef WaterScene_H
#define WaterScene_H

#include "Scene.h"
#include "PostProcessor.h"

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

	void SetPostProcessor(PostProcessor& postProcessor)
	{
		m_postProcessor = postProcessor;
	}

private:
	std::vector<Mesh *> boxes;
	PostProcessor m_postProcessor;
};

#endif // !WaterScene_H