#version 410 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 u_viewPos;
uniform int u_pointLights_count;
uniform int u_directionalLights_count;
#define MAX_POINT_LIGHTS 20
#define MAX_DIRECTIONAL_LIGHTS 5
uniform PointLight u_pointLights[MAX_POINT_LIGHTS];
uniform DirectionalLight u_directionalLights[MAX_DIRECTIONAL_LIGHTS];

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // Ambient
    vec3 ambient = light.ambient * 0.05;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;

    vec3 res = (ambient + diffuse);

    return res;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 viewDir) {
    // Ambient
    vec3 ambient = light.ambient * 0.05;

    // Diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;

    // Distance attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0 +  0.0014 * distance + 0.000007 * (distance * distance));

    vec3 res = (ambient + diffuse) * attenuation;

    return res;
}
  
void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < u_pointLights_count; i++)
        result += calculatePointLight(u_pointLights[i], norm, viewDir);
    for (int i = 0; i < u_directionalLights_count; i++)
        result += calculateDirectionalLight(u_directionalLights[i], norm, viewDir);
    
    float gamma = 2.2;
    FragColor = vec4(pow(result, vec3(1.0/gamma)), 1.0);
} 