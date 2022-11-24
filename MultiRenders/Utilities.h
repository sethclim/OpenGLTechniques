#ifndef UTILITIES_H
#define UTILITIES_H

#include "StandardIncludes.h"

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
	
};

#endif // !UTILITIES_H


