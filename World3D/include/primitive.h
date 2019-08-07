#pragma once

#include <math.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "solids/solids.h"

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
		      float scaleX, float scaleY, float scaleZ,
		      Solid solid);

	float x, y, z;
	glm::mat4 rotationState;
	float scaleX, scaleY, scaleZ;

	struct Color
	{
		float red = 1.0f;
		float green = 1.0f;
		float blue = 1.0f;
	};
	Color color;

	void translate(float dx, float dy, float dz);
	void rotate(float theta, float nx, float ny, float nz);

	void draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const;

	static void init();

private:
	unsigned int m_vao;
	unsigned int m_nIndices;
	bool m_withlighting;
	static Shader m_basicShader;
	static Shader m_lightingShader;

private:
	void draw_without_lighting(const glm::mat4& view, const glm::mat4& projection) const;
	void draw_with_lighting(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) const;
};