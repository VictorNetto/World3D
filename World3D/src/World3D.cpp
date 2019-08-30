#include "world3D.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "primitive.h"
#include "World3DObjects.h"

extern GLFWwindow* glfwWindow = nullptr;

using namespace World3D;

static void init_GLFW();
static void init_OpenGL();
static void init_ImGui();

static void terminate_ImGui();

void World3D::init()
{
	init_GLFW();
	init_OpenGL();
	init_ImGui();

	init_vertex_data();

	init_world_objects();
}

void World3D::terminate()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	terminate_ImGui();
}

static void init_GLFW()
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
	glfwWindow = glfwCreateWindow(1300, 700, "3D World", NULL, NULL);
	if (glfwWindow == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		std::cin.get();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(glfwWindow);

	// Turn vsync on
	glfwSwapInterval(1);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Anti Aliasing
	//--------------
	glEnable(GL_MULTISAMPLE);
}

static void init_OpenGL()
{
	// glew: loat all OpenGL function pointers
	// ---------------------------------------
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		std::cin.get();
		glfwTerminate();
		return;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
}

static void init_ImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

static void terminate_ImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}