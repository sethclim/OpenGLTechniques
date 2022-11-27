#ifndef SCENEONE_H
#define SCENEONE_H

#include "Scene.h"

class SceneOne : public Scene
{
public:
	SceneOne();
	SceneOne(Camera _camera);
	virtual ~SceneOne();

	void ProcessInput(float dt);

};

#endif // !SCENEONE_H


