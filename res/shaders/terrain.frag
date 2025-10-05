#version 410 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 u_viewPos;
uniform int u_pointLights_count;
#define MAX_POINT_LIGHTS 20
uniform PointLight u_pointLights[MAX_POINT_LIGHTS];

vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDir) {
    // Ambient
    vec3 ambient = pointLight.ambient * 0.05;

    // Diffuse
    vec3 lightDir = normalize(pointLight.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * pointLight.diffuse;

    // Distance attenuation
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 res = (ambient + diffuse) * attenuation;

    return res;
}
  
void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < u_pointLights_count; i++)
        result += calculatePointLight(u_pointLights[i], norm, viewDir);
    
    float gamma = 2.2;
    FragColor = vec4(pow(result, vec3(1.0/gamma)), 1.0);
} 