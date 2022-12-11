#include "Utilities.h"
#include "WindowController.h"

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



glm::vec3 Utilities::ViewToWorldCoordTransform(glm::vec2 _mouse, Camera _camera) {

	float x = 2.0 * _mouse.x / WindowController::GetInstance().GetResolution().m_width - 1;
	float y = 2.0 * _mouse.y / WindowController::GetInstance().GetResolution().m_height - 1;

	glm::vec3 cam_fwd = glm::normalize(glm::vec3(0) - _camera.GetPosition());
	glm::vec3 cam_to_light = glm::vec3(0.0f, 0.0f, 0.0f) - _camera.GetPosition();

	float diff = 1000.0 - 0.1;

	float eye_hit_z = -glm::length(cam_to_light) * glm::dot(cam_fwd, glm::normalize(cam_to_light));

	float ndc_depth = ((1000.0 + 0.1) + (2.0 * 1000.0 * 0.1) / eye_hit_z) / (1000.0 - 0.1);

	glm::mat4 ProjectView = _camera.GetProjection() * _camera.GetView();
	glm::mat4 viewProjectionInverse = glm::inverse(ProjectView);

	glm::vec4 screenPos = glm::vec4(x, -y, ndc_depth, 1.0f);
	glm::vec4 worldPos = viewProjectionInverse * screenPos;

	worldPos.w = 1 / worldPos.w;
	worldPos.y *= worldPos.w;
	worldPos.x *= worldPos.w;
	worldPos.z *= worldPos.w;

	return glm::vec3(worldPos);
}
