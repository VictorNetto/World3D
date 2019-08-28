#include "primitive.h"

#include <math.h>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace World3D;

static unsigned int _vaos[NUM_SOLIDS];
static unsigned int _nIndices[NUM_SOLIDS];

static void load_cube()
{
	unsigned int cube_vbo[3], cube_vao, cube_ebo;
	VertexData::cube::load();
	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(3, cube_vbo);
	glGenBuffers(1, &cube_ebo);
	_vaos[CUBE] = cube_vao;
	_nIndices[CUBE] = VertexData::cube::N_INDICES;

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

static void load_sphere()
{
	unsigned int sphere_vbo[2], sphere_vao, sphere_ebo;
	VertexData::sphere::load();
	glGenVertexArrays(1, &sphere_vao);
	glGenBuffers(2, sphere_vbo);
	glGenBuffers(1, &sphere_ebo);
	_vaos[SPHERE] = sphere_vao;
	_nIndices[SPHERE] = VertexData::sphere::N_INDICES;

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

static void load_cone()
{
	unsigned int cone_vbo, cone_vao, cone_ebo;
	cone::load();
	glGenVertexArrays(1, &cone_vao);
	glGenBuffers(1, &cone_vbo);
	glGenBuffers(1, &cone_ebo);
	_vaos[CONE] = cone_vao;
	_nIndices[CONE] = cone::N_INDICES;

	glBindVertexArray(cone_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cone_vbo);
	glBufferData(GL_ARRAY_BUFFER, cone::sizeof_vertices, cone::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cone_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cone::sizeof_indices, cone::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_cylinder()
{
	unsigned int cylinder_vbo, cylinder_vao, cylinder_ebo;
	cylinder::load();
	glGenVertexArrays(1, &cylinder_vao);
	glGenBuffers(1, &cylinder_vbo);
	glGenBuffers(1, &cylinder_ebo);
	_vaos[CYLINDER] = cylinder_vao;
	_nIndices[CYLINDER] = cylinder::N_INDICES;

	glBindVertexArray(cylinder_vao);

	glBindBuffer(GL_ARRAY_BUFFER, cylinder_vbo);
	glBufferData(GL_ARRAY_BUFFER, cylinder::sizeof_vertices, cylinder::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinder_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder::sizeof_indices, cylinder::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

static void load_solid(Solid solid, unsigned int* vao, unsigned int* nIndices)
{
	*vao = _vaos[solid];
	*nIndices = _nIndices[solid];
}

// ----------------------------------------------------------------------------
// -- Primitive ---------------------------------------------------------------
// ----------------------------------------------------------------------------
Primitive::Primitive(Light* light, Solid solid)
	: light { light }
{
	load_solid(solid, &m_vao, &m_nIndices);
}

// Code from Effective C++
glm::vec3& Primitive::position()
{
	return const_cast<glm::vec3&>(const_cast<const Primitive*>(this)->position());
}

// Code from Effective C++
glm::vec3& Primitive::scale()
{
	return const_cast<glm::vec3&>(const_cast<const Primitive*>(this)->scale());
}

// Code from Effective C++
glm::vec3& Primitive::rotation_axis()
{
	return const_cast<glm::vec3&>(const_cast<const Primitive*>(this)->rotation_axis());
}

// Code from Effective C++
float& Primitive::rotation_angle()
{
	return const_cast<float&>(const_cast<const Primitive*>(this)->rotation_angle());
}

void Primitive::translate(const glm::vec3& displacement)
{
	glm::vec3& oldPosition = position();
	oldPosition += displacement;
}

void Primitive::scale(const glm::vec3& scaleAmount)
{
	glm::vec3& oldScale = scale();
	oldScale *= scaleAmount;
}

void Primitive::rotate(const glm::vec3& rotationAxis, float angle)
{
	// Implement This!!!
}

void Primitive::rotate(float angle)
{
	//rotationAxis = rotation_axis();
}


#include <iostream>
void Primitive::draw() const
{
	// set up the model transformation
	glm::mat4 modelTranslate = glm::translate(glm::mat4(1.0f), position());
	glm::mat4 modelRotate = glm::rotate(glm::mat4(1.0f), rotation_angle(), rotation_axis());
	glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), scale());

	light->get_shader().use();
	light->get_shader().setMat4("model", modelTranslate * modelRotate * modelScale);
	light->get_shader().setVec3("objectColor", color);

	// finally draw the primitive
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
}

void World3D::init_vertex_data()
{
	static bool initialized = false;

	if (!initialized) {
		load_cube();
		load_sphere();
		load_cylinder();
		load_cone();

		initialized = true;
	}
}

// ----------------------------------------------------------------------------
// -- BasicPrimitive ----------------------------------------------------------
// ----------------------------------------------------------------------------

BasicPrimitive::BasicPrimitive(glm::vec3 position, glm::vec3 scale,
	glm::vec3 rotationAxis, float rotationAngle,
	Light* light, Solid solid)
	: Primitive{ light, solid }, m_position{ position }, m_scale{ scale },
	m_rotationAxis{ rotationAxis }, m_rotationAngle{ rotationAngle }
{
}

const glm::vec3& BasicPrimitive::position() const
{
	return m_position;
}

const glm::vec3& BasicPrimitive::scale() const
{
	return m_scale;
}

const glm::vec3& BasicPrimitive::rotation_axis() const
{
	return m_rotationAxis;
}

const float& BasicPrimitive::rotation_angle() const
{
	return m_rotationAngle;
}