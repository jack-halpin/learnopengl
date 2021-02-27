#version 330 core

struct Material {
    sampler2D diffuse; // Diffuse value is usually just the color of the object at a point. Also ambient is the same value as diffuse usually.
    sampler2D specular; //specular value depends on the point in the specular
    sampler2D emission;
    float shininess;
};

struct Light {
    //vec3 position; // Doing a point light so we don't need a position, just a direction
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  
};

uniform Material material;
uniform Light light;


out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec2 TexPos;
in vec3 FragPos;

void main()
{
	
	// Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));

    // Diffusion
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos)); 

    // Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));

    vec3 emission = vec3(0.0, 0.0, 0.0);
    if (texture(material.specular, TexPos).r == 0.0)
    {
        emission = vec3(texture(material.emission, TexPos));
    }
    

    vec3 result = ambient + diffuse + specular;// + emission;
    FragColor = vec4(result, 1.0);
}  