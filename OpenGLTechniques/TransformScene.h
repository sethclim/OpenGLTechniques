#ifndef TRANSFORMSCENE_H
#define TRANSFORMSCENE_H

#include "Scene.h"

class TransformScene : public Scene
{
public:
	TransformScene();
	TransformScene(Camera _camera);
	virtual ~TransformScene();

	void Init();

	void ProcessInput(float dt);

};

#endif // !TRANSFORMSCENE_H