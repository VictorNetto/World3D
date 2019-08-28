#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "shader.h"

namespace World3D {

	/*
		Light is a base class to make possible future implementation
		of multiple lights
	*/
	class Light
	{
	public:
		virtual Shader get_shader() = 0;
		virtual void update_uniforms() = 0;  // a function to be called before every draw

		static void init();
	};

	class NoLight : public Light {
	public:
		Shader get_shader();
		void update_uniforms() {}
	};

	class PhongLight : public Light {
	public:
		Shader get_shader();
		void update_uniforms();

		glm::vec3 position;
		glm::vec3 ambientLight;
		glm::vec3 diffuseLight;
		glm::vec3 specularLight;
		float ambientLightIntensity;
		float diffuseLightIntensity;
		float specularLightIntensity;
	};

	class PointLight : public Light {  // same as PhongLight but with an intensity attenuation
	public:
		Shader get_shader();
		void update_uniforms();

		glm::vec3 position;
		glm::vec3 ambientLight;
		glm::vec3 diffuseLight;
		glm::vec3 specularLight;
		float ambientLightIntensity;
		float diffuseLightIntensity;
		float specularLightIntensity;
		// attenuation
		float constant, linear, quadradic;
	};

	class Spotlight : public Light {
	public:
		Shader get_shader();
		void update_uniforms();

		glm::vec3 position;
		glm::vec3 ambientLight;
		glm::vec3 diffuseLight;
		glm::vec3 specularLight;
		float ambientLightIntensity;
		float diffuseLightIntensity;
		float specularLightIntensity;
		// attenuation
		float constant, linear, quadradic;
		// view direction and cutoff
		glm::vec3 direction;
		float cutOff, outerCutOff;
	};

}