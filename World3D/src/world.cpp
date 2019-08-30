#include "World.h"

using namespace World3D;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "World3DObjects.h"
#include "stb_image.h"

extern GLFWwindow* glfwWindow;

FrameRate World::m_frameRate;
Camera World::m_camera;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

World& World::get_instance()
{
	static World instance;

	return instance;
}

World::World()
	: m_window{ glfwWindow }
{
	// Set callback to GLFW
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
}

World::~World()
{
}

bool World::should_close() const
{
	return glfwWindowShouldClose(m_window);
}

void World::update()
{
	// poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwPollEvents();

	// update the frame rate
	m_frameRate.update();

	// update the camera
	m_camera.update(delta_time());

	update_uniforms();
}

void World::clear_buffers() const
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World::draw() const
{
	// draws attached objects
	for (Object* object : m_attachedObjects) {
		if (object->visible) object->draw();
	}
}

void World::swap_buffers() const
{
	glfwSwapBuffers(m_window);
}

float World::delta_time() const
{
	return m_frameRate.deltaTime;
}

void World::attach_object(Object* object)
{
	// Attaches object to the World
	// Attached objects will be drawn every frame
	if (object) {
		m_attachedObjects.push_back(object);
	}
}

void World::install_light(Light* light)
{
	// Adds light to the World and builds its Shader
	if (light) {
		light->get_shader().build();
		m_installedLights.push_back(light);
	}
}

void World::update_uniforms()
{
	for (Light* light : m_installedLights) {
		// Updates uniforms that light owns
		light->update_uniforms();
		
		// Updates uniforms related to the World
		light->get_shader().use();
		light->get_shader().setMat4("view", m_camera.view());
		light->get_shader().setMat4("projection", m_camera.projection());
	}
}

void World::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// ESC to exit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// ASDW movements
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W)
			m_camera.stop_move(FORWARD);
		if (key == GLFW_KEY_S)
			m_camera.stop_move(BACKWARD);
		if (key == GLFW_KEY_A)
			m_camera.stop_move(LEFT);
		if (key == GLFW_KEY_D)
			m_camera.stop_move(RIGHT);
	}
	else {
		if (key == GLFW_KEY_W)
			m_camera.move(FORWARD);
		if (key == GLFW_KEY_S)
			m_camera.move(BACKWARD);
		if (key == GLFW_KEY_A)
			m_camera.move(LEFT);
		if (key == GLFW_KEY_D)
			m_camera.move(RIGHT);
	}
}

void World::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) return;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
		m_camera.mouseButtonState[BUTTON_LEFT] = (action == GLFW_PRESS);
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		m_camera.mouseButtonState[BUTTON_RIGHT] = (action == GLFW_PRESS);
}

void World::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) return;

	m_camera.update_mouse((float)xpos, (float)ypos);
}

void World::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_camera.zoom((float)yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}