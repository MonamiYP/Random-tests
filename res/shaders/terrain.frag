#version 410 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 u_viewPos;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

float near = 1; 
float far  = 100; 
  
float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
    //ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * u_lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_lightColor; 

    vec4 result = vec4(ambient + diffuse + specular, 1.0);

    FragColor = result;

    // float depth = LinearizeDepth(gl_FragCoord.z) / far;
    // FragColor = result * vec4(1.0 * vec3((1-depth)/depth), 1.0);
} 