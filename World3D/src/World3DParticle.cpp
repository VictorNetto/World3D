#include "World3DParticle.h"

#include "glm/glm.hpp"

#include "primitive.h"

World3DParticle::World3DParticle()
{
	Primitive p{ 0, 0, 0, glm::mat4(1.0f), 0.025f, 0.025f, 0.025f, SPHERE_WITH_NORMALS };
	m_object.add_primitive(p);
	m_object.set_color(1.0f, 1.0f, 1.0f);
}

void World3DParticle::set_color(float r, float g, float b)
{
	m_object.set_color(r, g, b);
}

void World3DParticle::draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
{
	m_object.set_position(get_x(), get_y(), get_z());
	m_object.draw(view, projection, viewPos);
}