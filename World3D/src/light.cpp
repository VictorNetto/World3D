#include "light.h"

Shader noLightShader = Shader("./res/noLight.vs", "./res/noLight.fs");
Shader phongLightingShader = Shader("./res/phongLighting.vs", "./res/phongLighting.fs");
//Shader phongLighting = Shader("./res/phongLighting.vs", "./res/phongLighting.fs");

extern PhongLight phongLight = PhongLight();
extern NoLight noLight = NoLight();

void Light::init()
{
	noLightShader.build();
	phongLightingShader.build();

	phongLight.position = { 0, 0, 1 };
	phongLight.ambientLight = { 1, 1, 1 };
	phongLight.diffuseLight = { 1, 1, 1 };
	phongLight.specularLight = { 1, 1, 1 };
	phongLight.ambientLightIntensity = 0.1;
	phongLight.diffuseLightIntensity = 0.5;
	phongLight.specularLightIntensity = 0.8;
}

Shader NoLight::get_shader()
{
	return noLightShader;
}

Shader PhongLight::get_shader()
{
	return phongLightingShader;
}

void PhongLight::update_uniforms(const glm::mat4x4& view, const glm::mat4x4& model)
{
	get_shader().use();

	get_shader().setVec3("light.position", glm::vec3(view * model * glm::vec4(position, 1.0f)));
	get_shader().setVec3("light.ambient", ambientLight * ambientLightIntensity);
	get_shader().setVec3("light.diffuse", diffuseLight * diffuseLightIntensity);
	get_shader().setVec3("light.specular", specularLight * specularLightIntensity);
}