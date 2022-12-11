#ifndef MOVELIGHTSCENE_H
#define MOVELIGHTSCENE_H

#include "Scene.h"

class MoveLightScene : public Scene
{
public:
	MoveLightScene();
	MoveLightScene(Camera _camera);
	virtual ~MoveLightScene();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);

};

#endif // !MOVELIGHTSCENE_H


