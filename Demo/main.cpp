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
	float particleColor[3] = { 1, 0, 0 };
	float particlePositon[3] = { 1, 1, 1 };

	World3D ourWorld;
	//ourWorld.axesVisible = false;
	ourWorld.lightVisible = true;
	//ourWorld.floorVisible = true;

	Particle pa;

	ourWorld.add_particle(&pa);

	while (!ourWorld.should_close())
	{
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
	}

	return 0;
}