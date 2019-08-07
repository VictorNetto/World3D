#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "primitive.h"

class Object
{
public:
	Object();

	void add_primitive(const Primitive& primitive);
	void translate(float dx, float dy, float dz);
	void rotate(float theta, float nx, float ny, float nz);
	void draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const;
	void set_color(float r, float g, float b);

private:
	std::vector<Primitive> m_primitives;
};