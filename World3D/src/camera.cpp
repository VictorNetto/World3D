#include "camera.h"

// Default camera values
// initial values
static const float PHY = 225.0f;
static const float THETA = 125.3f;
static const float FOV = 55.0f;
// max/min values
static const float MAX_FOV = 120.0f;
static const float MIN_FOV = 1.0f;
static const float MAX_THETA = 179.0f;
static const float MIN_THETA = 1.0f;
// camera movements
static const float CAMERA_SPEED = 5.0f;
static int cameraMovingStatus[] = { 0, 0, 0, 0 };  // cameraMovingStatus[FORWARD] = 0 -> no moving forward; cameraMovingStatus[FORWARD] = 1 -> moving forward; ...

Camera::Camera()
	: m_position{ glm::vec3(3.0f, 3.0f, 3.0f)},
	mouseButtonState{ false, false }
{
	set_fov(FOV);
	set_direction(PHY, THETA);
}

glm::mat4 Camera::view() const
{
	return glm::lookAt(m_position, m_position + m_cameraDirection, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Camera::projection() const
{
	return glm::perspective(glm::radians(m_fov), 1.0f, 0.1f, 100.0f);
}

glm::vec3 Camera::position() const
{
	return m_position;
}

void Camera::update(float deltaTime)
{
	m_position += camera_velocity() * deltaTime;
}

void Camera::move(Camera_Movement direction) const
{
	cameraMovingStatus[direction] = 1;
}

void Camera::stop_move(Camera_Movement direction) const
{
	cameraMovingStatus[direction] = 0;
}

void Camera::update_mouse(float x, float y)
{
	m_mousePosition.x = x;
	m_mousePosition.y = y;

	// left button processing
	if (mouseButtonState[BUTTON_LEFT])
	{
		process_mouse_left(m_buttonLeftPressed.x - x, m_buttonLeftPressed.y - y);
	}
	else
	{
		m_buttonLeftPressed.x = x;
		m_buttonLeftPressed.y = y;
		m_positionWhenLeftWasPressed = m_position;
	}

	// right button processing
	if (mouseButtonState[BUTTON_RIGHT])
	{
		process_mouse_right(m_buttonRightPressed.x - x, m_buttonRightPressed.y - y);
	}
	else
	{
		m_buttonRightPressed.x = x;
		m_buttonRightPressed.y = y;
		m_phyWhenRightWasPressed = m_phy;
		m_thetaWhenRightWasPressed = m_theta;
	}
}

void Camera::zoom(float dy)
{
	set_fov(m_fov - dy);
}

glm::vec3 Camera::camera_velocity() const
{
	glm::vec3 vel(0.0f, 0.0f, 0.0f);

	vel += m_cameraRight * (float)(cameraMovingStatus[RIGHT] - cameraMovingStatus[LEFT]);
	vel += m_cameraDirection * (float)(cameraMovingStatus[FORWARD] - cameraMovingStatus[BACKWARD]);
	vel = vel * ( 1.0f / vel.length() );

	return vel * CAMERA_SPEED;
}

void Camera::set_direction(float new_phy, float new_theta)
{
	if (new_theta > MAX_THETA) m_theta = MAX_THETA;
	else if (new_theta < MIN_THETA) m_theta = MIN_FOV;
	else m_theta = new_theta;
	m_phy = new_phy;

	float phy_r = glm::radians(m_phy);
	float theta_r = glm::radians(m_theta);
	m_cameraDirection = glm::vec3(cosf(phy_r) * sinf(theta_r), sinf(phy_r) * sinf(theta_r), cosf(theta_r));
	m_cameraRight = glm::normalize(glm::cross(m_cameraDirection, glm::vec3(0.0f, 0.0f, 1.0f)));
	m_cameraUp = glm::cross(m_cameraRight, m_cameraDirection);
}

void Camera::set_fov(float new_fov)
{
	if (new_fov > MAX_FOV) m_fov = MAX_FOV;
	else if (new_fov < MIN_FOV) m_fov = MIN_FOV;
	else m_fov = new_fov;
}

void Camera::process_mouse_left(float dx, float dy)
{
	dx /= 100.0f;
	dy /= 100.0f;
	m_position = m_positionWhenLeftWasPressed - m_cameraUp * dy + m_cameraRight * dx;
}

void Camera::process_mouse_right(float dx, float dy)
{
	dx *= 0.25f;
	dy *= 0.25f;
	set_direction(m_phyWhenRightWasPressed + dx, m_thetaWhenRightWasPressed - dy);
}