#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "solids/solids.h"
#include "light.h"

enum Solid {
	CONE,
	CUBE,
	CYLINDER,
	SPHERE,

	CUBE_WITH_NORMALS,
	SPHERE_WITH_NORMALS,

	NUM_SOLIDS
};

struct Primitive
{
	Primitive();
	Primitive(float x, float y, float z, glm::mat4 rotationState,
		      float scaleX, float scaleY, float scaleZ, Light* light,
		      Solid solid);

	float x, y, z;
	glm::mat4 rotationState;
	float scaleX, scaleY, scaleZ;

	glm::vec3 color = glm::vec3(1.0f);

	void translate(float dx, float dy, float dz);
	void rotate(float theta, float nx, float ny, float nz);
	void set_position(float newX, float newY, float newZ);

	void draw() const;
	//void draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const;

	static void init();

private:
	unsigned int m_vao;
	unsigned int m_nIndices;
	Light* m_light;
	//bool m_withlighting;
	//static Shader m_basicShader;
	//static Shader m_lightingShader;

private:
	//void draw_without_lighting(const glm::mat4& view, const glm::mat4& projection) const;
	//void draw_with_lighting(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const;
};