#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "primitive.h"
#include "light.h"

class Object
{
public:
	Object();

	void add_primitive(const Primitive& primitive);
	void translate(float dx, float dy, float dz);
	void rotate(float theta, float nx, float ny, float nz);
	void set_position(float newX, float newY, float newZ);  // apply the new position to all object's primitives
	void draw() const;
	void set_color(float r, float g, float b);
	void set_light(Light* light);

private:
	std::vector<Primitive> m_primitives;
};