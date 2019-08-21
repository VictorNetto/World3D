#include "light.h"

Shader noLightShader = Shader("./res/noLight.vs", "./res/noLight.fs");
Shader phongLightingShader = Shader("./res/phongLighting.vs", "./res/phongLighting.fs");

extern PhongLight phongLight = PhongLight();
extern NoLight noLight = NoLight();

void Light::init()
{
	noLightShader.build();
	phongLightingShader.build();
}

Shader NoLight::get_shader()
{
	return noLightShader;
}

Shader PhongLight::get_shader()
{
	return phongLightingShader;
}

void PhongLight::update_uniforms()
{
	get_shader().use();

	get_shader().setVec3("light.position", position);
	get_shader().setVec3("light.ambient", ambientLight * ambientLightIntensity);
	get_shader().setVec3("light.diffuse", diffuseLight * diffuseLightIntensity);
	get_shader().setVec3("light.specular", specularLight * specularLightIntensity);
}