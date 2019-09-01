#include "primitive.h"

#include <math.h>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace World3D;

static unsigned int _vaos[NUM_SOLIDS];
static unsigned int _nIndices[NUM_SOLIDS];

static void load_cone(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	unsigned int* vao, unsigned int* nIndices)
{
	unsigned int cone_vbo, cone_vao, cone_ebo;
	static bool basiVertexDataInitialized = false;

	// Initialize basic vertex data
	if (!basiVertexDataInitialized)
	{
		VertexData::cone::load_basic_vertex_data();
		basiVertexDataInitialized = true;
	}

	// Initialize our specific data
	VertexData::cone::load_specific_vertex_data(position, scale, rotationAxis, rotationAngle);

	glGenVertexArrays(1, &cone_vao);
	glGenBuffers(1, &cone_vbo);
	glGenBuffers(1, &cone_ebo);
	*vao = cone_vao;
	*nIndices = VertexData::cone::N_INDICES;

	glBindVertexArray(cone_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexData::cone::sizeof_vertices, VertexData::cone::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexData::cone::sizeof_indices, VertexData::cone::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_cube(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	unsigned int* vao, unsigned int* nIndices)
{
	unsigned int cube_vbo[3], cube_vao, cube_ebo;
	static bool basiVertexDataInitialized = false;

	// Initialize basic vertex data
	if (!basiVertexDataInitialized)
	{
		VertexData::cube::load_basic_vertex_data();
		basiVertexDataInitialized = true;
	}

	// Initialize our specific data
	VertexData::cube::load_specific_vertex_data(position, scale, rotationAxis, rotationAngle);

	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(3, cube_vbo);
	glGenBuffers(1, &cube_ebo);
	*vao = cube_vao;
	*nIndices = VertexData::cube::N_INDICES;

	glBindVertexArray(cube_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, VertexData::cube::sizeof_vertices, VertexData::cube::vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, VertexData::cube::sizeof_normals, VertexData::cube::normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, VertexData::cube::sizeof_textCoordinates, VertexData::cube::textCoordinates, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexData::cube::sizeof_indices, VertexData::cube::indices, GL_STATIC_DRAW);
}

static void load_cylinder(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	unsigned int* vao, unsigned int* nIndices)
{
	unsigned int cylinder_vbo, cylinder_vao, cylinder_ebo;
	static bool basiVertexDataInitialized = false;

	// Initialize basic vertex data
	if (!basiVertexDataInitialized)
	{
		VertexData::cylinder::load_basic_vertex_data();
		basiVertexDataInitialized = true;
	}

	// Initialize our specific data
	VertexData::cylinder::load_specific_vertex_data(position, scale, rotationAxis, rotationAngle);

	glGenVertexArrays(1, &cylinder_vao);
	glGenBuffers(1, &cylinder_vbo);
	glGenBuffers(1, &cylinder_ebo);
	*vao = cylinder_vao;
	*nIndices = VertexData::cylinder::N_INDICES;

	glBindVertexArray(cylinder_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexData::cylinder::sizeof_vertices, VertexData::cylinder::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexData::cylinder::sizeof_indices, VertexData::cylinder::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_sphere(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	unsigned int* vao, unsigned int* nIndices)
{
	unsigned int sphere_vbo[2], sphere_vao, sphere_ebo;
	static bool basiVertexDataInitialized = false;

	// Initialize basic vertex data
	if (!basiVertexDataInitialized)
	{
		VertexData::sphere::load_basic_vertex_data();
		basiVertexDataInitialized = true;
	}

	// Initialize our specific data
	VertexData::sphere::load_specific_vertex_data(position, scale, rotationAxis, rotationAngle);

	glGenVertexArrays(1, &sphere_vao);
	glGenBuffers(2, sphere_vbo);
	glGenBuffers(1, &sphere_ebo);
	*vao = sphere_vao;
	*nIndices = VertexData::sphere::N_INDICES;

	glBindVertexArray(sphere_vao);

	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, VertexData::sphere::sizeof_vertices, VertexData::sphere::vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, VertexData::sphere::sizeof_normals, VertexData::sphere::normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexData::sphere::sizeof_indices, VertexData::sphere::indices, GL_STATIC_DRAW);
}

static void load_solid(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	Solid solid, unsigned int* vao, unsigned int* nIndices)
{
	if (solid == CONE)
	{
		load_cone(position, scale, rotationAxis, rotationAngle, vao, nIndices);
	}
	else if (solid == CUBE)
	{
		load_cube(position, scale, rotationAxis, rotationAngle, vao, nIndices);
	}
	else if (solid == CYLINDER)
	{
		load_cylinder(position, scale, rotationAxis, rotationAngle, vao, nIndices);
	}
	else if (solid == SPHERE)
	{
		load_sphere(position, scale, rotationAxis, rotationAngle, vao, nIndices);
	}
}

// ----------------------------------------------------------------------------
// -- Primitive ---------------------------------------------------------------
// ----------------------------------------------------------------------------
Primitive::Primitive(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle,
	Light* light, Solid solid)
	: light { light }
{
	load_solid(position, scale, rotationAxis, rotationAngle, solid, &m_vao, &m_nIndices);
}

void Primitive::draw(const glm::vec3& position, const glm::vec3& scale,
	const glm::vec3& rotationAxis, float rotationAngle) const
{
	// set up the model transformation
	glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 modelRotate = glm::rotate(glm::mat4(1.0f), rotationAngle, rotationAxis);
	glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), scale);

	light->get_shader().use();
	light->get_shader().setMat4("model", modelTranslate * modelRotate * modelScale);
	light->get_shader().setVec3("objectColor", color);

	// finally draw the primitive
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
}