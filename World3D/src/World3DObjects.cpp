#include <math.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "primitive.h"
#include "object.h"

const float PI = atanf(1) * 4;

extern Object worldAxes = Object();
extern Object worldLight = Object();
extern Object worldFloor = Object();
extern Object worldCube = Object();

extern NoLight noLight;
extern PhongLight phongLight;
extern PointLight pointLight;

// worldAxes Primitives
// x axis
Primitive p1, p2;
// y axis
Primitive p3, p4;
// z axis
Primitive p5, p6;

static void construct_worldAxes()
{
	// x axis
	p1 = Primitive( 0.4f, 0.0f, 0.0f, glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0, 1, 0)),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER );
	p2 = Primitive( 0.9f, 0.0f, 0.0f, glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0, 1, 0)),
		0.05f, 0.05f, 0.10f, &noLight, CONE );
	// y axis
	p3 = Primitive( 0.0f, 0.4f, 0.0f, glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(1, 0, 0)),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER );
	p4 = Primitive( 0.0f, 0.9f, 0.0f, glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(1, 0, 0)),
		0.05f, 0.05f, 0.10f, &noLight, CONE );
	// z axis
	Object axis_z;
	p5 = Primitive( 0.0f, 0.0f, 0.4f, glm::mat4(1.0f),
		0.01f, 0.01f, 0.4f, &noLight, CYLINDER );
	p6 = Primitive( 0.0f, 0.0f, 0.9f, glm::mat4(1.0f),
		0.05f, 0.05f, 0.10f, &noLight, CONE );

	p1.set_color(1.0f, 0.0f, 0.0f);
	p2.set_color(1.0f, 0.0f, 0.0f);

	p3.set_color(0.0f, 1.0f, 0.0f);
	p4.set_color(0.0f, 1.0f, 0.0f);

	p5.set_color(0.0f, 0.0f, 1.0f);
	p6.set_color(0.0f, 0.0f, 1.0f);

	worldAxes.add_primitive(p1);
	worldAxes.add_primitive(p2);
	worldAxes.add_primitive(p3);
	worldAxes.add_primitive(p4);
	worldAxes.add_primitive(p5);
	worldAxes.add_primitive(p6);
}

// worldLight Primitive
Primitive p_light;

static void construct_worldLight()
{
	p_light = Primitive(phongLight.position.x, phongLight.position.y, phongLight.position.z, glm::mat4(1.0f),
		0.05f, 0.05f, 0.05f, &noLight, CUBE);
	worldLight.add_primitive(p_light);
}

// worldFloor Primitive
Primitive p_floor;

static void construct_worldFloor()
{
	p_floor = Primitive(0.0f, 0.0f, 0.0f, glm::mat4(1.0f),
		10.0f, 10.0f, 0.001f, &pointLight, CUBE_WITH_NORMALS);
	p_floor.set_color(0.2f, 0.3f, 0.3f);
	worldFloor.add_primitive(p_floor);
}

// worldFloor Primitive
Primitive p_cube;

static void construct_cube()
{
	p_cube = Primitive(-0.5f, -0.5f, 0.5f, glm::mat4(1.0f),
		1.0f, 1.0f, 1.0f, &pointLight, CUBE_WITH_NORMALS);
	//p_floor.set_color(0.2f, 0.3f, 0.3f);
	worldCube.add_primitive(p_cube);
}

void init_world_objects()
{
	construct_worldAxes();
	construct_worldLight();
	construct_worldFloor();

	construct_cube();
}