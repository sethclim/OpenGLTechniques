#ifndef UTILITIES_H
#define UTILITIES_H

#include "StandardIncludes.h"
#include "Camera.h"

namespace Utilities
{

	class FPSCounter
	{
	public:
		static int _fpsCount;
		static int FPS;

		static std::chrono::time_point<std::chrono::steady_clock> lastTime;

		static void CalculateFrameRate();

	};

	glm::vec3 ViewToWorldCoordTransform(glm::vec2 _mouse, Camera _camera);
	
};

#endif // !UTILITIES_H


