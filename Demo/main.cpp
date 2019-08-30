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
	//worldFloor.set_light(&pointLight);
	//worldFloor.visible = false;

	while (!ourWorld.should_close())
	{
		// clear buffers, pool and events and update the world
		ourWorld.update();
		ourWorld.clear_buffers();

		// draw the objects in the world
		ourWorld.draw();

		ourWorld.swap_buffers();
	}

	World3D::terminate();

	return 0;
}
