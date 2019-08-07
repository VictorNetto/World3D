#pragma once

#include "object.h"

class World3DParticle {
public:
	World3DParticle();

	void set_color(float r = 1.0f, float g = 1.0f, float b = 1.0f);
	void draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos);

	virtual float get_x() const { return 0.0f; };
	virtual float get_y() const { return 0.0f; };
	virtual float get_z() const { return 0.0f; };

private:
	float m_old_x, m_old_y, m_old_z;
	Object m_object;
};