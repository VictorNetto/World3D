#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "shader.h"

/*
	Light is a base class to make possible future implementation
	of multiple lights
*/
class Light
{
public:
	virtual Shader get_shader() = 0;
	virtual void update_uniforms(const glm::mat4x4& view, const glm::mat4x4& projection) = 0;  // a function to be called before every draw

	static void init();
};

class NoLight : public Light {
public:
	Shader get_shader();
	void update_uniforms(const glm::mat4x4& view, const glm::mat4x4& model) {}
};

class PhongLight : public Light {
public:
	Shader get_shader();
	void update_uniforms(const glm::mat4x4& view, const glm::mat4x4& model);

	glm::vec3 position;
	glm::vec3 ambientLight;
	glm::vec3 diffuseLight;
	glm::vec3 specularLight;
	float ambientLightIntensity;
	float diffuseLightIntensity;
	float specularLightIntensity;
};