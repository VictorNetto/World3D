#include "World3DParticle.h"

#include "glm/glm.hpp"

#include "primitive.h"

World3DParticle::World3DParticle()
{
	m_old_x = get_x();
	m_old_y = get_y();
	m_old_z = get_z();

	Primitive p{ m_old_x, m_old_y, m_old_z, glm::mat4(1.0f), 0.025f, 0.025f, 0.025f, SPHERE_WITH_NORMALS };
	m_object.add_primitive(p);
	m_object.set_color(1.0f, 1.0f, 1.0f);
}

void World3DParticle::set_color(float r, float g, float b)
{
	m_object.set_color(r, g, b);
}

void World3DParticle::draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
{
	float new_x, new_y, new_z;

	new_x = get_x();
	new_y = get_y();
	new_z = get_z();

	m_object.translate(new_x - m_old_x, new_y - m_old_y, new_z - m_old_z);
	m_object.draw(view, projection, viewPos);

	m_old_x = new_x;
	m_old_y = new_y;
	m_old_z = new_z;

}