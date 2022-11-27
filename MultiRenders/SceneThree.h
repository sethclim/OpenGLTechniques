#ifndef SceneThree_H
#define SceneThree_H

#include "Scene.h"

class SceneThree : public Scene
{
public:
	SceneThree();
	SceneThree(Camera _camera);
	virtual ~SceneThree();

	void ProcessInput(float dt);

};

#endif // !SCENETHREE_H