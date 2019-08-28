#include "World.h"

using namespace World3D;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "World3DObjects.h"
#include "stb_image.h"

extern NoLight noLight;
extern PhongLight phongLight;
extern PointLight pointLight;
extern Spotlight spotlight;

extern Object worldFloor;

extern GLFWwindow* glfwWindow;

FrameRate World::m_frameRate;
Camera World::m_camera;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void load_textures()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("./res/floor.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	spotlight.get_shader().use(); // don't forget to activate/use the shader before setting uniforms!
	spotlight.get_shader().setInt("ourTexture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

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

	// Initializes subsystems
	Light::init();

	// load textures
	load_textures();
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

void World::clear() const
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World::draw() const
{

	// draw floor
	if (floorVisible)
		worldFloor.draw();
}

void World::swap_buffers() const
{
	glfwSwapBuffers(m_window);
}

float World::delta_time() const
{
	return m_frameRate.deltaTime;
}

void World::update_uniforms()
{
	noLight.update_uniforms();
	phongLight.update_uniforms();
	pointLight.update_uniforms();
	spotlight.update_uniforms();

	noLight.get_shader().use();
	noLight.get_shader().setMat4("view", m_camera.view());
	noLight.get_shader().setMat4("projection", m_camera.projection());

	phongLight.get_shader().use();
	phongLight.get_shader().setMat4("view", m_camera.view());
	phongLight.get_shader().setMat4("projection", m_camera.projection());
	phongLight.get_shader().setVec3("viewPos", m_camera.position());

	pointLight.get_shader().use();
	pointLight.get_shader().setMat4("view", m_camera.view());
	pointLight.get_shader().setMat4("projection", m_camera.projection());
	pointLight.get_shader().setVec3("viewPos", m_camera.position());


	spotlight.get_shader().use();
	spotlight.get_shader().setMat4("view", m_camera.view());
	spotlight.get_shader().setMat4("projection", m_camera.projection());
	spotlight.get_shader().setVec3("viewPos", m_camera.position());
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