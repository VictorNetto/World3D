#include "World3D.h"

#include <math.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "primitive.h"

const float PI = atanf(1) * 4;

extern PhongLight phongLight;
extern NoLight noLight;

FrameRate World3D::m_frameRate;
Camera World3D::m_camera;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void initialize_ImGui(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

static void ImGui_terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

World3D::World3D()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Anti Aliasing
	// -------------
	glfwWindowHint(GLFW_SAMPLES, 9);

	// glfw window creation
	// --------------------
	m_window = glfwCreateWindow(600, 600, "3D World", NULL, NULL);
	if (m_window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		std::cin.get();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);

	// Set callback to GLFW
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	// glew: loat all OpenGL function pointers
	// ---------------------------------------
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		std::cin.get();
		glfwTerminate();
		return;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Anti Aliasing
	//--------------
	glEnable(GL_MULTISAMPLE);

	// ImGui
	//------
	initialize_ImGui(m_window);

	// Initialize the Primitive
	// ------------------------
	Primitive::init();

	// Initializa lights
	// ----------------
	Light::init();

	// Set a default fps
	m_frameRate.set_frame_rate(60.0f);


	// Contruct the xyz axes
	// ---------------------
	Object axis_x;
	Primitive p1{ 0.4f, 0.0f, 0.0f, glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0, 1, 0)),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER };
	Primitive p2{ 0.9f, 0.0f, 0.0f, glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0, 1, 0)),
		0.05f, 0.05f, 0.10f, &noLight, CONE };
	axis_x.add_primitive(p1);
	axis_x.add_primitive(p2);
	axis_x.set_color(1.0f, 0.0f, 0.0f);

	Object axis_y;
	Primitive p3{ 0.0f, 0.4f, 0.0f, glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(1, 0, 0)),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER };
	Primitive p4{ 0.0f, 0.9f, 0.0f, glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(1, 0, 0)),
		0.05f, 0.05f, 0.10f, &noLight, CONE };
	axis_y.add_primitive(p3);
	axis_y.add_primitive(p4);
	axis_y.set_color(0.0f, 1.0f, 0.0f);

	Object axis_z;
	Primitive p5{ 0.0f, 0.0f, 0.4f, glm::mat4(1.0f),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER };
	Primitive p6{ 0.0f, 0.0f, 0.9f, glm::mat4(1.0f),
		0.05f, 0.05f, 0.10f, &noLight, CONE };
	axis_z.add_primitive(p5);
	axis_z.add_primitive(p6);
	axis_z.set_color(0.0f, 0.0f, 1.0f);

	m_axes.push_back(axis_x);
	m_axes.push_back(axis_y);
	m_axes.push_back(axis_z);

	// Construct the light
	// -------------------
	Primitive p_light(phongLight.position.x, phongLight.position.y, phongLight.position.z, glm::mat4(1.0f),
		0.05f, 0.05f, 0.05f, &noLight, CUBE);
	lightObejct.add_primitive(p_light);
	lightObejct.set_color(phongLight.diffuseLight.r, phongLight.diffuseLight.g, phongLight.diffuseLight.b);

	// Construct the floor
	// -------------------

	Primitive p_floor(0.0f, 0.0f, 0.0f, glm::mat4(1.0f),
		10.0f, 10.0f, 0.01f, &phongLight, CUBE_WITH_NORMALS);
	m_floor.add_primitive(p_floor);
	m_floor.set_color(0.2f, 0.3f, 0.3f);

}

World3D::~World3D()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	// shut down ImGui
	ImGui_terminate();
}

bool World3D::should_close() const
{
	return glfwWindowShouldClose(m_window);
}

void World3D::update()
{
	// poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwPollEvents();

	// update the frame rate
	m_frameRate.update();
	m_frameRate.show_frame_rate();

	// update the camera
	m_camera.update(delta_time());
}

void World3D::clear() const
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void World3D::draw() const
{
	update_uniforms();

	// draw axes
	if (axesVisible)
		for (Object object : m_axes) object.draw();

	// draw light
	if (lightVisible)
		lightObejct.draw();

	// draw floor
	if (floorVisible)
		m_floor.draw();

	// draw particles
	for (World3DParticle* particle : m_particles) particle->draw();
}

void World3D::swap_buffers() const
{
	glfwSwapBuffers(m_window);
}

void World3D::set_frame_rate(float frameRateToKeep)
{
	m_frameRate.set_frame_rate(frameRateToKeep);
}

float World3D::delta_time() const
{
	return m_frameRate.deltaTime;
}

void World3D::update_uniforms()
{
	glm::mat4 id4 = glm::mat4(1.0f);
	glm::mat4 lightModel = glm::translate(id4, phongLight.position);

	noLight.update_uniforms(m_camera.view(), id4);
	phongLight.update_uniforms(m_camera.view(), lightModel);

	noLight.get_shader().use();
	noLight.get_shader().setMat4("view", m_camera.view());
	noLight.get_shader().setMat4("projection", m_camera.projection());

	phongLight.get_shader().use();
	phongLight.get_shader().setMat4("view", m_camera.view());
	phongLight.get_shader().setMat4("projection", m_camera.projection());
}

void World3D::add_particle(World3DParticle* particle)
{
	m_particles.push_back(particle);
}


void World3D::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void World3D::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) return;

	if (button == GLFW_MOUSE_BUTTON_LEFT)
		m_camera.mouseButtonState[BUTTON_LEFT] = (action == GLFW_PRESS);
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		m_camera.mouseButtonState[BUTTON_RIGHT] = (action == GLFW_PRESS);
}

void World3D::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) return;

	m_camera.update_mouse((float)xpos, (float)ypos);
}

void World3D::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_camera.zoom((float)yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}