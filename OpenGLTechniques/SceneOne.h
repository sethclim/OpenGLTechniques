#ifndef SCENEONE_H
#define SCENEONE_H

#include "Scene.h"

class SceneOne : public Scene
{
public:
	SceneOne();
	SceneOne(Camera _camera);
	virtual ~SceneOne();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);

};

#endif // !SCENEONE_H


