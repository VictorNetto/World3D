#include "World3DObjects.h"

using namespace World3D;

#include <math.h>

#include <glm/vec3.hpp>

#include "primitive.h"
#include "object.h"

const float PI = atanf(1) * 4;

extern Object worldAxes = Object();
extern Object worldFloor = Object();

extern NoLight noLight;
extern PhongLight phongLight;

// worldAxes ------------------------------------------------------------------
// ----------------------------------------------------------------------------
BasicPrimitive xAxis, xAxisArrow;
BasicPrimitive yAxis, yAxisArrow;
BasicPrimitive zAxis, zAxisArrow;

static void construct_worldAxes()
{
	// x axis
	xAxis = BasicPrimitive(glm::vec3(0.4, 0.0, 0.0), glm::vec3(0.01, 0.01, 0.4), glm::vec3(0, 1, 0), PI / 2,
		&noLight, CYLINDER);
	xAxis.color = glm::vec3(1, 0, 0);
	xAxisArrow = BasicPrimitive(glm::vec3(0.9, 0.0, 0.0), glm::vec3(0.05, 0.05, 0.10), glm::vec3(0, 1, 0), PI / 2,
		&noLight, CONE);
	xAxisArrow.color = glm::vec3(1, 0, 0);

	// y axis
	yAxis = BasicPrimitive(glm::vec3(0.0, 0.4, 0.0), glm::vec3(0.01, 0.01, 0.4), glm::vec3(1, 0, 0), -PI / 2,
		&noLight, CYLINDER);
	yAxis.color = glm::vec3(0, 1, 0);
	yAxisArrow = BasicPrimitive(glm::vec3(0.0, 0.9, 0.0), glm::vec3(0.05, 0.05, 0.10), glm::vec3(1, 0, 0), -PI / 2,
		&noLight, CONE);
	yAxisArrow.color = glm::vec3(0, 1, 0);

	// z axis
	zAxis = BasicPrimitive(glm::vec3(0.0, 0.0, 0.4), glm::vec3(0.01, 0.01, 0.4), glm::vec3(1, 0, 0), 0,
		&noLight, CYLINDER);
	zAxis.color = glm::vec3(0, 0, 1);
	zAxisArrow = BasicPrimitive(glm::vec3(0.0, 0.0, 0.9), glm::vec3(0.05, 0.05, 0.10), glm::vec3(1, 0, 0), 0,
		&noLight, CONE);
	zAxisArrow.color = glm::vec3(0, 0, 1);

	worldAxes.add_primitive(&xAxis);
	worldAxes.add_primitive(&xAxisArrow);
	worldAxes.add_primitive(&yAxis);
	worldAxes.add_primitive(&yAxisArrow);
	worldAxes.add_primitive(&zAxis);
	worldAxes.add_primitive(&zAxisArrow);
}

// worldFloor -----------------------------------------------------------------
// ----------------------------------------------------------------------------
BasicPrimitive p_floor;

static void construct_worldFloor()
{
	p_floor = BasicPrimitive(glm::vec3(0, 0, 0), glm::vec3(10, 10, 0.01), glm::vec3(0, 0, 1), 0,
	&phongLight, CUBE);
	p_floor.color = glm::vec3(1, 0, 0);
	worldFloor.add_primitive(&p_floor);
}

void World3D::init_world_objects()
{
	construct_worldAxes();
	construct_worldFloor();
}