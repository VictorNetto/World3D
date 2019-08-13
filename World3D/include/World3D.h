#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "frameRate.h"
#include "camera.h"
#include "World3DParticle.h"

class World3D
{
public:
	World3D();
	~World3D();

	bool should_close() const;
	void update();
	void clear() const;
	void draw() const;
	void set_frame_rate(float frameRateToKeep);
	float delta_time() const;

	bool axesVisible = true;
	bool lightVisible = false;
	bool floorVisible = false;

private:
	static FrameRate m_frameRate;
	static Camera m_camera;
	GLFWwindow* m_window;
	std::vector<Object> m_axes;
	Object m_light;
	Object m_floor;

	// particles stuff --------------------------------------------------------
	// ------------------------------------------------------------------------
public:
	void add_particle(World3DParticle* particle);

private:
	std::vector<World3DParticle*> m_particles;

	// callback functions -----------------------------------------------------
	// ------------------------------------------------------------------------
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};