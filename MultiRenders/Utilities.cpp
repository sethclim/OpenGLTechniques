#include "Utilities.h"

int Utilities::FPSCounter::_fpsCount = 0;
int Utilities::FPSCounter::FPS = 0;

std::chrono::time_point<std::chrono::steady_clock> Utilities::FPSCounter::lastTime = std::chrono::steady_clock::now();

void Utilities::FPSCounter::CalculateFrameRate()
{
    auto currentTime = std::chrono::steady_clock::now();

    const auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
    ++_fpsCount;

    if (elapsedTime > 1000000000) {
        lastTime = currentTime;
        FPS = _fpsCount;
        _fpsCount = 0;
    }
}
