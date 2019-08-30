#include "object.h"

using namespace World3D;

Object::Object()
	: m_primitives{}
{}

void Object::add_primitive(Primitive* primitive)
{
	m_primitives.push_back(primitive);
}

void Object::translate(const glm::vec3& displacement)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->translate(displacement);
	}
}

void Object::scale(const glm::vec3& scaleAmount)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->scale(scaleAmount);
	}
}

void Object::rotate(const glm::vec3& rotationAxis, float angle)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->rotate(rotationAxis, angle);
	}
}

void Object::rotate(float angle)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->rotate(angle);
	}
}

void Object::set_position(const glm::vec3& position)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->position() = position;
	}
}

void Object::set_scale(const glm::vec3& scale)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->scale() = scale;
	}
}

void Object::set_rotation_axis(const glm::vec3& rotationAxis)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->rotation_axis() = rotationAxis;
	}
}

void Object::set_rotation_angle(float angle)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->rotation_angle() = angle;
	}
}

void Object::draw() const
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->draw();
	}
}

void Object::set_color(const glm::vec3& newColor)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
		m_primitives[i]->color = newColor;
}

void Object::set_light(Light* light)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
		m_primitives[i]->light = light;
}