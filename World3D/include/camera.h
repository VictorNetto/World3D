#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement
// Used as abstraction to stay away from window-system specific input methods
// --------------------------------------------------------------------------
enum Camera_Movement {
	FORWARD = 0,
	BACKWARD,
	RIGHT,
	LEFT
};

enum Mouse_Button {
	BUTTON_LEFT = 0,
	BUTTON_RIGHT
};

class Camera
{
public:
	Camera();

	glm::mat4 view() const;
	glm::mat4 projection() const;

	glm::vec3 position() const;

	void update(float deltaTime);

	void move(Camera_Movement direction) const;
	void stop_move(Camera_Movement direction) const;
	
	void update_mouse(float x, float y);
	void zoom(float dy);
	
	bool mouseButtonState[2];

private:
	float m_phy, m_theta;
	float m_fov;
	glm::vec3 m_position;
	glm::vec3 m_cameraDirection, m_cameraRight, m_cameraUp;

	glm::vec3 camera_velocity() const;

	void set_direction(float new_phy, float new_theta);
	void set_fov(float new_fov);

	// Members variable/functions to deal with mouse events
	struct MouseEvent
	{
		float x, y;
	};
	MouseEvent m_mousePosition;
	MouseEvent m_buttonLeftPressed;
	MouseEvent m_buttonRightPressed;
	glm::vec3 m_positionWhenLeftWasPressed;
	float m_phyWhenRightWasPressed, m_thetaWhenRightWasPressed;

	void process_mouse_left(float dx, float dy);
	void process_mouse_right(float dx, float dy);
};