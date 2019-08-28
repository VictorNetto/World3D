#include "light.h"

using namespace World3D;

Shader noLightShader = Shader("./res/noLight.vs", "./res/noLight.fs");
Shader phongLightingShader = Shader("./res/phongLighting.vs", "./res/phongLighting.fs");
Shader pointLightingShader = Shader("./res/pointLighting.vs", "./res/pointLighting.fs");
Shader spotlightShader = Shader("./res/spotlight.vs", "./res/spotlight.fs"); 

extern PhongLight phongLight = PhongLight();
extern NoLight noLight = NoLight();
extern PointLight pointLight = PointLight();
extern Spotlight spotlight = Spotlight();

void Light::init()
{
	noLightShader.build();
	phongLightingShader.build();
	pointLightingShader.build();
	spotlightShader.build();
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

Shader PointLight::get_shader()
{
	return pointLightingShader;
}

void PointLight::update_uniforms()
{
	get_shader().use();

	get_shader().setVec3("light.position", position);
	get_shader().setVec3("light.ambient", ambientLight * ambientLightIntensity);
	get_shader().setVec3("light.diffuse", diffuseLight * diffuseLightIntensity);
	get_shader().setVec3("light.specular", specularLight * specularLightIntensity);
	get_shader().setFloat("light.constant", constant);
	get_shader().setFloat("light.linear", linear);
	get_shader().setFloat("light.quadradic", quadradic);
}

Shader Spotlight::get_shader()
{
	return spotlightShader;
}

void Spotlight::update_uniforms()
{
	get_shader().use();

	get_shader().setVec3("light.position", position);
	get_shader().setVec3("light.ambient", ambientLight * ambientLightIntensity);
	get_shader().setVec3("light.diffuse", diffuseLight * diffuseLightIntensity);
	get_shader().setVec3("light.specular", specularLight * specularLightIntensity);
	get_shader().setFloat("light.constant", constant);
	get_shader().setFloat("light.linear", linear);
	get_shader().setFloat("light.quadradic", quadradic);
	get_shader().setVec3("light.direction", direction);
	get_shader().setFloat("light.cutOff", cutOff);
	get_shader().setFloat("light.outerCutOff", outerCutOff);
}