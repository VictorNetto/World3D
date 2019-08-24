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

void particle_a_ImGui(Particle* p);
void particle_b_ImGui(Particle* p);
void worldLight_ImGui();
void pointLightAttenuation_ImGui();
void spotlight_params_ImGui();
void miscellaneous_ImGui(World3D* world);
void whichLight_ImGui(Particle* p1, Particle* p2);

extern Object worldLight;
extern Object worldFloor;
extern Object worldCube;

extern NoLight noLight;
extern PhongLight phongLight;
extern PointLight pointLight;
extern Spotlight spotlight;

int main()
{
	World3D ourWorld;

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

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		particle_a_ImGui(&pa);
		particle_b_ImGui(&pb);
		worldLight_ImGui();
		pointLightAttenuation_ImGui();
		spotlight_params_ImGui();
		miscellaneous_ImGui(&ourWorld);
		whichLight_ImGui(&pa, &pb);

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ourWorld.swap_buffers();
	}

	return 0;
}

void particle_a_ImGui(Particle* p)
{
	static float particleColor[3] = { 1, 0, 0 };
	static float particlePositon[3] = { 1, 1, 1 };

	ImGui::Begin("Particle A");
	ImGui::SliderFloat3("Position", particlePositon, -1.0f, 1.0f);
	ImGui::ColorEdit3("Color", particleColor);
	ImGui::End();

	p->x = particlePositon[0];
	p->y = particlePositon[1];
	p->z = particlePositon[2];
	p->set_color(particleColor[0], particleColor[1], particleColor[2]);
}

void particle_b_ImGui(Particle* p)
{
	static float omega = 1;
	static float xMax = 0.75;
	static float yMax = 0.5;

	ImGui::Begin("Particle B");
	ImGui::SliderFloat("Angular Velocity", &omega, -5.0f, 5.0f);
	ImGui::SliderFloat("X Amplitude", &xMax, 0.5f, 2.0f);
	ImGui::SliderFloat("Y Amplitude", &yMax, 0.5f, 2.0f);
	ImGui::End();

	p->x = xMax * cosf(omega * glfwGetTime());
	p->y = yMax * sinf(omega * glfwGetTime());
}

void worldLight_ImGui()
{
	static float lightPositon[3] = { 0, 0, 1 };

	static float ambientColor[3] = { 1, 1, 1 };
	static float diffuseColor[3] = { 1, 1, 1 };
	static float specularColor[3] = { 1, 1, 1 };

	static float intensities[3] = { 0.1, 0.5, 0.8 };

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

	pointLight.position = glm::vec3(lightPositon[0], lightPositon[1], lightPositon[2]);
	pointLight.ambientLight = glm::vec3(ambientColor[0], ambientColor[1], ambientColor[2]);
	pointLight.diffuseLight = glm::vec3(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
	pointLight.specularLight = glm::vec3(specularColor[0], specularColor[1], specularColor[2]);
	pointLight.ambientLightIntensity = intensities[0];
	pointLight.diffuseLightIntensity = intensities[1];
	pointLight.specularLightIntensity = intensities[2];

	spotlight.position = glm::vec3(lightPositon[0], lightPositon[1], lightPositon[2]);
	spotlight.ambientLight = glm::vec3(ambientColor[0], ambientColor[1], ambientColor[2]);
	spotlight.diffuseLight = glm::vec3(diffuseColor[0], diffuseColor[1], diffuseColor[2]);
	spotlight.specularLight = glm::vec3(specularColor[0], specularColor[1], specularColor[2]);
	spotlight.ambientLightIntensity = intensities[0];
	spotlight.diffuseLightIntensity = intensities[1];
	spotlight.specularLightIntensity = intensities[2];
}

void pointLightAttenuation_ImGui()
{
	static float constantAttenuation = 1.0;
	static float linearAttenuation = 0.09;
	static float quadradicAttenuation = 0.032;

	ImGui::Begin("Point Light Attenuation");
	ImGui::SliderFloat("Constant", &constantAttenuation, 0, 2);
	ImGui::SliderFloat("Linear", &linearAttenuation, 0, 2);
	ImGui::SliderFloat("Quadradic", &quadradicAttenuation, 0, 2);
	ImGui::End();

	pointLight.constant = constantAttenuation;
	pointLight.linear = linearAttenuation;
	pointLight.quadradic = quadradicAttenuation;

	spotlight.constant = constantAttenuation;
	spotlight.linear = linearAttenuation;
	spotlight.quadradic = quadradicAttenuation;
}

void spotlight_params_ImGui()
{
	// spotlight direction
	static float theta = 180;
	static float phi = 0;
	static float cutOff = 30;
	static float edge = 10;

	float t, p;

	ImGui::Begin("Spotlight Parameters");
	ImGui::SliderFloat("Theta", &theta, 0, 180);
	ImGui::SliderFloat("Phi", &phi, 0, 360);
	ImGui::SliderFloat("Cutoff", &cutOff, 0, 180);
	ImGui::SliderFloat("Edge", &edge, 0, 45);
	ImGui::End();

	if (theta < 0) theta = 0;
	if (theta > 180) theta = 180;
	if (phi < 0) phi = 0;
	if (phi > 360) phi = 360;
	if (cutOff < 0) cutOff = 0;
	if (cutOff > 180) cutOff = 180;
	if (edge < 0) edge = 0;
	if (edge + cutOff > 180) edge = 180 - cutOff;

	t = glm::radians(theta);
	p = glm::radians(phi);

	spotlight.direction = glm::vec3(cosf(p)*sinf(t), sinf(p)*sinf(t), cosf(t));
	spotlight.cutOff = cosf(glm::radians(cutOff));
	spotlight.outerCutOff = cosf(glm::radians(cutOff + edge));;
}

void miscellaneous_ImGui(World3D* world)
{
	ImGui::Begin("Miscellaneous");
	ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("World Axes Visible", &(world->axesVisible));
	ImGui::Checkbox("World Light Visible", &(world->lightVisible));
	ImGui::Checkbox("World Floor Visible", &(world->floorVisible));
	//ImGui::Text("Application average %.1f ms/frame (%.1f FPS)", 1000 * ourWorld.delta_time(), 1/ourWorld.delta_time());
	ImGui::End();
}

void whichLight_ImGui(Particle* p1, Particle* p2)
{
	static int e = 1;

	int old_e = e;
	ImGui::Begin("Light to Apply");
	ImGui::RadioButton("No Lighting", &e, -1); ImGui::SameLine();
	ImGui::RadioButton("Phong Lighting", &e, 0);
	ImGui::RadioButton("Point Lighting", &e, 1); ImGui::SameLine();
	ImGui::RadioButton("Spotlight", &e, 2);
	ImGui::End();
	if (old_e == e) return;

	if (e == -1) {
		worldFloor.set_light(&noLight);
		worldCube.set_light(&noLight);
		p1->set_light(&noLight);
		p2->set_light(&noLight);
	} else if (e == 0) {
		worldFloor.set_light(&phongLight);
		worldCube.set_light(&phongLight);
		p1->set_light(&phongLight);
		p2->set_light(&phongLight);
	} else if (e == 1) {
		worldFloor.set_light(&pointLight);
		worldCube.set_light(&pointLight);
		p1->set_light(&pointLight);
		p2->set_light(&pointLight);
	} else if (e == 2) {
		worldFloor.set_light(&spotlight);
		worldCube.set_light(&spotlight);
		p1->set_light(&spotlight);
		p2->set_light(&spotlight);
	}
}