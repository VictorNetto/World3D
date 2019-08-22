#pragma once

#include "object.h"
#include "light.h"

class World3DParticle {
public:
	World3DParticle();

	void set_color(float r = 1.0f, float g = 1.0f, float b = 1.0f);
	void draw();
	void set_light(Light* light);

	virtual float get_x() const { return 0.0f; };
	virtual float get_y() const { return 0.0f; };
	virtual float get_z() const { return 0.0f; };

private:
	Object m_object;
};