#include <iostream>
#include <math.h>

#include "World3D.h"
#include "light.h"
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

	extern PhongLight phongLight;
	extern Object worldLight;
	float lightPositon[3] = { 0, 0, 1 };
	float ambientColor[3] = { 1, 1, 1 };
	float diffuseColor[3] = { 1, 1, 1 };
	float specularColor[3] = { 1, 1, 1 };
	float intensities[3] = { 0.1, 0.5, 0.8 };

	World3D ourWorld;
	//ourWorld.axesVisible = false;
	ourWorld.lightVisible = true;
	//ourWorld.floorVisible = true;

	Particle pa, pb;

	ourWorld.add_particle(&pa);
	ourWorld.add_particle(&pb);

	while (!ourWorld.should_close())
	{
		// clear buffers, pool and events and update the world
		ourWorld.update();
		ourWorld.clear();

		// draw the objects in the world
		ourWorld.draw();

		pb.x = 0.65*cosf(glfwGetTime());
		pb.y = 0.75*sinf(glfwGetTime());

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		ImGui::Begin("Particle Position and Color");
		ImGui::SliderFloat3("Position", particlePositon, -1.0f, 1.0f);
		ImGui::ColorEdit3("Color", particleColor);
		ImGui::End();

		pa.x = particlePositon[0];
		pa.y = particlePositon[1];
		pa.z = particlePositon[2];
		pa.set_color(particleColor[0], particleColor[1], particleColor[2]);

		ImGui::Begin("Light Positions and Colors");
		ImGui::SliderFloat3("Position", lightPositon, -1.0f, 1.0f);
		ImGui::ColorEdit3("Ambiente", ambientColor);
		ImGui::ColorEdit3("Diffuse", diffuseColor);
		ImGui::ColorEdit3("Specular", specularColor);
		ImGui::SliderFloat3("Intensities", intensities, 0.0f, 1.0f);
		ImGui::End();

		worldLight.set_position(lightPositon[0], lightPositon[1], lightPositon[2]);
		worldLight.set_color(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
		phongLight.position = glm::vec3(lightPositon[0], lightPositon[1], lightPositon[2]);
		phongLight.ambientLight = glm::vec3(ambientColor[0], ambientColor[1], ambientColor[2]);
		phongLight.diffuseLight = glm::vec3(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
		phongLight.specularLight = glm::vec3(specularColor[0], specularColor[1], specularColor[2]);
		phongLight.ambientLightIntensity = intensities[0];
		phongLight.diffuseLightIntensity = intensities[1];
		phongLight.specularLightIntensity = intensities[2];

		ImGui::Begin("Hello, world!");
		ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Checkbox("World Axes Visible", &ourWorld.axesVisible);
		ImGui::Checkbox("World Light Visible", &ourWorld.lightVisible);
		ImGui::Checkbox("World Floor Visible", &ourWorld.floorVisible);
		//ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000 * ourWorld.delta_time(), 1/ourWorld.delta_time());
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ourWorld.swap_buffers();
	}

	return 0;
}