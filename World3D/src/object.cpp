#include "object.h"

Object::Object()
	: m_primitives{}
{}

void Object::add_primitive(const Primitive& primitive)
{
	m_primitives.push_back(primitive);
}

void Object::translate(float dx, float dy, float dz)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i].translate(dx, dy, dz);
	}
}

void Object::rotate(float theta, float nx, float ny, float nz)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i].rotate(theta, nx, ny, nz);
	}
}

void Object::set_position(float newX, float newY, float newZ)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i].set_position(newX, newY, newZ);
	}
}

void Object::draw() const
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i].draw();
	}
}

/*void Object::draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i].draw(view, projection, viewPos);
	}
}*/

void Object::set_color(float r, float g, float b)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
		m_primitives[i].set_color(r, g, b);
}

void Object::set_light(Light* light)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
		m_primitives[i].set_light(light);
}