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

		void draw() const;

		void set_color(const glm::vec3& newColor);
		void set_light(Light* light);

	private:
		std::vector<Primitive*> m_primitives;
	};

}