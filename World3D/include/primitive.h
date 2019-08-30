#pragma once

#include <glm/vec3.hpp>

#include "solids/solids.h"
#include "light.h"

namespace World3D {

	/*
		Initializes solid's VertexData and load them into GPU
	*/
	void init_vertex_data();

	enum Solid {
		CONE,
		CUBE,
		CYLINDER,
		SPHERE,

		NUM_SOLIDS
	};

	/*
		In World3D, Primitive is the basic element in the world. Each
		primitive has an associate positition, scale, and rotation state,
		as well as a Light. This make possible fine grained rendering for
		primitives.

		Position, Scale and Rotation are virtual functions to permit the use
		of World3D with another codes that deal with this parameters. For example,
		a Physic Engine.

		TODO: add textures;
	*/
	class Primitive
	{
	protected:
		Primitive() : light{ nullptr }, m_vao{ 0 }, m_nIndices{ 0 } {}
	public:
		Primitive(Light* light, Solid solid);

		// virtual functions used by the draw function
		// to build and modify the model matrix
		virtual const glm::vec3& position() const = 0;
		virtual const glm::vec3& scale() const = 0;
		virtual const glm::vec3& rotation_axis() const = 0;
		virtual const float& rotation_angle() const = 0;

		glm::vec3& position();
		glm::vec3& scale();
		glm::vec3& rotation_axis();
		float& rotation_angle();

		// utility functions
		void translate(const glm::vec3& displacement);
		void scale(const glm::vec3& scaleAmount);
		void rotate(const glm::vec3& rotationAxis, float angle);
		void rotate(float angle);

		void draw() const;

		glm::vec3 color;
		Light* light;

	private:
		// OpenGl stuff
		unsigned int m_vao;
		unsigned int m_nIndices;
	};

	class BasicPrimitive : public Primitive
	{
	public:
		BasicPrimitive() : m_rotationAngle { 0 } {}

		BasicPrimitive(glm::vec3 position, glm::vec3 scale,
			glm::vec3 rotationAxis, float rotationAngle,
			Light* light, Solid solid);

		virtual const glm::vec3& position() const;
		virtual const glm::vec3& scale() const;
		virtual const glm::vec3& rotation_axis() const;
		virtual const float& rotation_angle() const;

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotationAxis;
		float m_rotationAngle;
	};

}