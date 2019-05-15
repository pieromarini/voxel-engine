#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {

	// ambient
	float ambientStrenght = 0.3;
	vec3 ambient = ambientStrenght * lightColor * vec3(texture(texture_diffuse1, TexCoord));

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * vec3(texture(texture_diffuse1, TexCoord));

	// specular
	/*
	float specularStrength = 0.1;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  
	*/
            
    vec3 result = ambient + diffuse; 
    FragColor = vec4(result, 1.0);
}
