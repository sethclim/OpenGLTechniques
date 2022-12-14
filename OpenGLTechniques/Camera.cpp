#include "Camera.h"

Camera::Camera()
{
	m_projection = { };
	m_view = { };
	m_position = { };
}

Camera::Camera(Resolution _screenResolution)
{
	m_position = { 0, 0 , 5};
	m_projection = glm::perspective(glm::radians(45.0f), (float)_screenResolution.m_width / (float)_screenResolution.m_height, 0.1f, 1000.0f);

	m_view = glm::lookAt(
		m_position,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

Camera::~Camera() { }

void Camera::Rotate()
{
	m_angle += 0.1f;
	m_lookAt.x = glm::cos(glm::radians(m_angle)) * 100;
	m_lookAt.z = glm::sin(glm::radians(m_angle)) * 100;

	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		glm::vec3(0, 1, 0)
	);
}