#version 330 core

in vec2 outTexCoords;
in vec3 outNormCoords;
in vec3 outFragCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

out vec4 FragColor;

void main() {
    vec3 ambient = light.ambient * texture(material.diffuse, outTexCoords).rgb;

    vec3 normal = normalize(outNormCoords);
    vec3 lightDirection = normalize(light.position - outFragCoords);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, outTexCoords).rgb;

    vec3 viewDirection = normalize(viewPosition - outFragCoords);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 64.0);
    vec3 specular = light.specular * spec * texture(material.specular, outTexCoords).rgb;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}
