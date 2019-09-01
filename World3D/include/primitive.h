#pragma once

#include <glm/vec3.hpp>

#include "solids/solids.h"
#include "light.h"

namespace World3D {

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
		used in the load functions to pass correct vertex data to GPU,
		as well as a Light and a Color. This make possible fine grained
		rendering for primitives.

		TODO: add textures;
	*/
	class Primitive
	{
	public:
		Primitive() : light{ nullptr }, m_vao{ 0 }, m_nIndices{ 0 } {}

		Primitive(const glm::vec3& position, const glm::vec3& scale,
			const glm::vec3& rotationAxis, float rotationAngle,
			Light* light, Solid solid);

		void draw(const glm::vec3& position, const glm::vec3& scale, 
			const glm::vec3& rotationAxis, float rotationAngle) const;

		glm::vec3 color;
		Light* light;

	private:
		// OpenGl stuff
		unsigned int m_vao;
		unsigned int m_nIndices;
	};

}