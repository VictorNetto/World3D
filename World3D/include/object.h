#pragma once

#include <vector>

#include <glm/vec3.hpp>

#include "primitive.h"
#include "light.h"

namespace World3D {

	class Object
	{
	public:
		Object();

		bool visible = true;

		// Virtual functions used to access the object's
		// position, scale and rotation.
		virtual const glm::vec3& position() const;
		virtual const glm::vec3& scale() const;
		virtual const glm::vec3& rotation_axis() const;
		virtual const float& rotation_angle() const;

		// Functions build upon the virtual const functions
		// with the same name. Affects all object's primitives
		// at once and change the primitive's position, scale
		// and rotation based on their state at the time they
		// were added to the Object.
		//glm::vec3& position();
		//glm::vec3& scale();
		//glm::vec3& rotation_axis();
		//float& rotation_angle();

		// Functions to move and scale the object. These
		// functions are based in the current object's state.
		// Affects all object's primitives at once and
		// change the primitive's position, scale and
		// rotation based on their state at the time
		// they were added to the Object.
		void translate(const glm::vec3& displacement);
		void scale(const glm::vec3& scaleAmount);
		void rotate(const glm::vec3& rotationAxis, float angle);
		void rotate(float angle);

		// Functions to move and scale the object. These
		// functions are based in the initial object's state.
		// Affects all object's primitives at once and
		// change the primitive's position, scale and
		// rotation based on their state at the time
		// they were added to the Object.
		void set_position(const glm::vec3& position);
		void set_scale(const glm::vec3& scale);
		void set_rotation_axis(const glm::vec3& rotationAxis);
		void set_rotation_angle(float angle);

		void add_primitive(Primitive* primitive);

		void draw() const;

		void set_color(const glm::vec3& color);
		void set_light(Light* light);

	private:
		// Internal representation of object's position,
		// scale and rotation
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotationAxis;
		float m_rotationAngle;

		// Struct to hold the layout of the primitive
		// at the time it's added to the object.
		// Hold a pointer to the primitive as well.
		struct PrimitiveLayout {
			Primitive* primitive;
			glm::vec3 position;
			glm::vec3 scale;
			glm::vec3 rotationAxis;
			float rotationAngle;
		};
		std::vector<Object::PrimitiveLayout> m_primitives;
	};

}