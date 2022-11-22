#ifndef APPLICATION_H
#define APPLICATION_H

#include "StandardIncludes.h"
#include "WindowController.h"
#include "GameController.h"

class Application :public Singleton<Application>
{
public:
	Application();
	virtual ~Application();

	void Initialize();
	void Run();

private:
	float m_LastFrameTime;

	GameController* m_gameController;
};

#endif // !APPLICATION_H


