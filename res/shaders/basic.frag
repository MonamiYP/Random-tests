#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
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

uniform sampler2D texture_diffuse1;
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

    // Specular;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * pointLight.specular;

    // Distance attenuation
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    vec3 res = (ambient + diffuse + specular) * attenuation;

    return res;
}

void main() {    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < u_pointLights_count; i++)
        result += calculatePointLight(u_pointLights[i], norm, viewDir);
    
    float gamma = 2.2;
    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;
    texColor = pow(texColor, vec3(gamma));
    vec3 color = result * texColor;
    FragColor = vec4(pow(color, vec3(1.0/gamma)), 1.0);
}