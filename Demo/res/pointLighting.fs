#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoord;

out vec4 FragColor;

struct Light {
    vec3 position;  // is supposed to be in world space
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadradic;
};
uniform Light light;

uniform vec3 objectColor;
uniform vec3 viewPos;

uniform sampler2D ourTexture;

float compute_attenuation(float d)
{
    return 1.0 / (light.constant + light.linear * d + light.quadradic * d * d);
}

void main()
{
    float distance = length(light.position - FragPos);
    float attenuation = compute_attenuation(distance);
    
    // ambient light
    vec3 ambient = light.ambient;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = (light.position - FragPos) / distance;
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.diffuse;

    // specular light
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), 32) * light.specular;

    vec3 result = (ambient + specular) * objectColor * attenuation;
    result += diffuse * texture(ourTexture, TextCoord).rgb * attenuation;
    FragColor = vec4(result, 1.0);
}
