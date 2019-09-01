#include <iostream>

#include "world3D.h"

extern World3D::Object worldFloor;
extern World3D::Object worldAxes;

extern World3D::NoLight noLight;
extern World3D::PhongLight phongLight;
extern World3D::PointLight pointLight;

int main()
{
	World3D::init();

	World3D::World& ourWorld = World3D::World::get_instance();
	ourWorld.install_light(&noLight);
	ourWorld.install_light(&phongLight);
	ourWorld.install_light(&pointLight);

	ourWorld.attach_object(&worldFloor);
	ourWorld.attach_object(&worldAxes);
	worldFloor.set_light(&pointLight);
	worldFloor.visible = false;

	World3D::Primitive p1(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0.5), glm::vec3(0, 0, 1), glm::radians(30.0), &phongLight, World3D::CUBE);
	World3D::Primitive p2(glm::vec3(0, 0, 0.5), glm::vec3(0.25), glm::vec3(0, 0, 1), glm::radians(0.0), &phongLight, World3D::SPHERE);
	p1.color = { 0.2, 0.5, 0.8 };
	p2.color = { 0.8, 0.5, 0.2 };
	World3D::Object sphere;
	sphere.add_primitive(&p1);
	sphere.add_primitive(&p2);
	ourWorld.attach_object(&sphere);

	while (!ourWorld.should_close())
	{
		// clear buffers, pool and events and update the world
		ourWorld.update();
		ourWorld.clear_buffers();

		// draw the objects in the world
		ourWorld.draw();

		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			static float position[3] = { 0, 0, 0 };
			static float scale[3] = { 1, 1, 1 };
			static float theta = 180;
			static float phi = 0;
			static float rotationAngle = 0;
			float t, p;

			ImGui::Begin("Cube Rotation");
			ImGui::SliderFloat3("Position", position, -1, 1);
			ImGui::SliderFloat3("Scale", scale, -1, 1);
			ImGui::SliderFloat("Rotation Axis Theta", &theta, 0, 180);
			ImGui::SliderFloat("Rotation Axis Phi", &phi, 0, 360);
			ImGui::SliderFloat("Rotation Angle", &rotationAngle, 0, 360);
			ImGui::End();
			t = glm::radians(theta);
			p = glm::radians(phi);

			//sphere.set_position(glm::vec3(position[0], position[1], position[2]));
			sphere.position() =  glm::vec3(position[0], position[1], position[2]);
			sphere.scale() =  glm::vec3(scale[0], scale[1], scale[2]);
			sphere.rotation_axis() = glm::vec3(cosf(p)*sinf(t), sinf(p)*sinf(t), cosf(t));
			sphere.rotation_angle() = glm::radians(rotationAngle);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		ourWorld.swap_buffers();
	}

	World3D::terminate();

	return 0;
}
