#include "object.h"

using namespace World3D;

Object::Object()
	: m_position{ glm::vec3(0) }, m_scale{ glm::vec3(1) },
	m_rotationAxis{ glm::vec3(0, 0, 1) }, m_rotationAngle{ 0 }
{
}

const glm::vec3& Object::position() const
{
	return m_position;
}

const glm::vec3& Object::scale() const
{
	return m_scale;
}
const glm::vec3& Object::rotation_axis() const
{
	return m_rotationAxis;
}

const float& Object::rotation_angle() const
{
	return m_rotationAngle;
}


// Code from Effective C++
glm::vec3& Object::position()
{
	return const_cast<glm::vec3&>(const_cast<const Object*>(this)->position());
}

// Code from Effective C++
glm::vec3& Object::scale()
{
	return const_cast<glm::vec3&>(const_cast<const Object*>(this)->scale());
}

// Code from Effective C++
glm::vec3& Object::rotation_axis()
{
	return const_cast<glm::vec3&>(const_cast<const Object*>(this)->rotation_axis());
}

// Code from Effective C++
float& Object::rotation_angle()
{
	return const_cast<float&>(const_cast<const Object*>(this)->rotation_angle());
}

void Object::translate(const glm::vec3& displacement)
{
	m_position += displacement;
}

void Object::scale(const glm::vec3& scaleAmount)
{
}

void Object::rotate(const glm::vec3& rotationAxis, float angle)
{
}

void Object::rotate(float angle)
{
}

void Object::add_primitive(Primitive* primitive)
{
	m_primitives.push_back(primitive);
}

void Object::draw() const
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->draw(position(), scale(), rotation_axis(), rotation_angle());
	}
}

void Object::set_color(const glm::vec3& color)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->color = color;
	}
}

void Object::set_light(Light* light)
{
	for (unsigned int i = 0; i < m_primitives.size(); i++)
	{
		m_primitives[i]->light = light;
	}
}