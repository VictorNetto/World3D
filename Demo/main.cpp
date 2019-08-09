#include <iostream>
#include <math.h>

#include "World3D.h"
#include "World3DParticle.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Particle : public World3DParticle {
public:
	Particle() : x{ 0 }, y{ 0 }, z{ 0 } {}

	float x, y, z;

	float get_x() const { return x; }
	float get_y() const { return y; }
	float get_z() const { return z; }
};

int main()
{
	float particleColor[3];
	float particlePositon[3];

	World3D ourWorld;
	//ourWorld.axesVisible = false;
	ourWorld.lightVisible = true;
	//ourWorld.floorVisible = true;

	Particle pa;

	ourWorld.add_particle(&pa);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(ourWorld.get_glfw_window() , true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	while (!ourWorld.should_close())
	{
		World3D::mouseOverImGui = io.WantCaptureMouse;

		// clear buffers, pool and events and update the world
		ourWorld.update();
		ourWorld.clear();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		ImGui::Begin("Particle Position and Color");
		ImGui::SliderFloat3("X - Y - Z", particlePositon, -1.0f, 1.0f);
		ImGui::ColorEdit3("Color", particleColor);
		ImGui::End();

		pa.x = particlePositon[0];
		pa.y = particlePositon[1];
		pa.z = particlePositon[2];
		pa.set_color(particleColor[0], particleColor[1], particleColor[2]);

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ourWorld.draw();

		//std::cout << io.WantCaptureMouse << std::endl;
	}

	return 0;
}