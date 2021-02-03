#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform PointLight pointLight;
uniform vec3 viewPosition;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 result = calcPointLight(pointLight, normal, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}