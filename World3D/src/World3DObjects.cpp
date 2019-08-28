#include "World3DObjects.h"

using namespace World3D;

#include <glm/vec3.hpp>

#include "primitive.h"
#include "object.h"

extern Object worldFloor = Object();

extern NoLight noLight;
extern PointLight pointLight;

// worldFloor Primitive
BasicPrimitive p_floor;

static void construct_worldFloor()
{
	p_floor = BasicPrimitive(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0, 0, 1), 0,
	&noLight, CUBE);
	p_floor.color = glm::vec3(1, 0, 0);
	worldFloor.add_primitive(&p_floor);
}

void World3D::init_world_objects()
{
	construct_worldFloor();
}