#ifndef SceneTwo_H
#define SceneTwo_H

#include "Scene.h"

class SceneTwo : public Scene
{
public:
	SceneTwo();
	SceneTwo(Camera _camera);
	virtual ~SceneTwo();

	void Init();

	void ProcessInput(float dt);

};

#endif // !SCENEONE_H