#include "Application.h"

int main()
{
	Application::GetInstance().Initialize();
	Application::GetInstance().Run();

	return 0;
}
