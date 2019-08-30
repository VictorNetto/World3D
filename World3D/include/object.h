#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "primitive.h"
#include "light.h"

namespace World3D {

	class Object
	{
	public:
		Object();

		bool visible = true;

		void add_primitive(Primitive* primitive);

		void translate(const glm::vec3& displacement);
		void scale(const glm::vec3& scaleAmount);
		void rotate(const glm::vec3& rotationAxis, float angle);
		void rotate(float angle);

		// Functions to set position, scale and rotation of objects
		// Corresponding functions will be called for every
		// objects's primitives. Most usefull for objects built with
		// just one primitive
		void set_position(const glm::vec3& position);
		void set_scale(const glm::vec3& scale);
		void set_rotation_axis(const glm::vec3& rotationAxis);
		void set_rotation_angle(float angle);

		void draw() const;

		void set_color(const glm::vec3& newColor);
		void set_light(Light* light);

	private:
		std::vector<Primitive*> m_primitives;
	};

}