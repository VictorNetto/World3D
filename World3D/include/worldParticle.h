#pragma once

#include "object.h"

class World3DParticle {
public:
	World3DParticle();

	void set_color(float r, float g, float b);
	void draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos);

	virtual float get_x() const = 0;
	virtual float get_y() const = 0;
	virtual float get_z() const = 0;

private:
	Object m_object;
};