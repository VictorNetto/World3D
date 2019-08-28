#include <iostream>

#include "world3D.h"


int main()
{
	World3D::init();

	World3D::World& ourWorld = World3D::World::get_instance();


	while (!ourWorld.should_close())
	{
		// clear buffers, pool and events and update the world
		ourWorld.update();
		ourWorld.clear();

		// draw the objects in the world
		ourWorld.draw();

		ourWorld.swap_buffers();
	}

	World3D::terminate();

	return 0;
}
