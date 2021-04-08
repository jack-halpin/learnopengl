#version 330 core

struct Material {
    sampler2D diffuse; // Diffuse value is usually just the color of the object at a point. Also ambient is the same value as diffuse usually.
    sampler2D specular; //specular value depends on the point in the specular
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position; // Doing a point light so we don't need a position, just a direction
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  

    float cutOff; // Splotlight
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
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
    // For spotlight we need to check the cutoff angle
    vec3 lightDir = normalize(light.position - FragPos);

    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

    if (theta > light.outerCutOff)
    {
        // Ambient
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));

        // Diffusion
        vec3 norm = normalize(Normal);

        // DIRECITONAL LIGHTING
        //vec3 lightDir = normalize(light.direction);

        // POINT LIGHTING
        // A point light will lose intensity as as object is further away
        // Adjusting the intensity based on distance from light is known
        // as attenuation. Check out https://learnopengl.com/Lighting/Light-casters
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
                    light.quadratic * (distance * distance));  


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

        // POINT lighting, adjust light attributes based on attenuation

        //ambient  *= attenuation; 
        diffuse  *= intensity;
        specular *= intensity;

        vec3 result = ambient + diffuse + specular;// + emission;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexPos)), 1.0);
    }

	
}  