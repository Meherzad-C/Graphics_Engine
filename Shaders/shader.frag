#version 400

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 vertexOut;
in vec4 colourOut;
in vec2 textureOut;
in vec3 normalOut;

out vec4 fragColour;

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

uniform bool isLit;
uniform bool isTextured;
uniform sampler2D textureImage;

void main()
{
	if (isLit)
	{
		// Ambient
		vec3 ambientColour = light.ambient * material.ambient;

		// Diffuse
		vec3 normal = normalize(normalOut);
		vec3 lightDirection = normalize(light.position - vertexOut);
		float lightIntensity = max(dot(lightDirection, normal), 0.0);
		vec3 diffuseColour = light.diffuse * material.diffuse * lightIntensity;

		// Specular
		vec3 viewDirection = normalize(cameraPosition - vertexOut);
		vec3 reflection = reflect(-lightDirection, normal);
		float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
		vec3 specularColour = light.specular * material.specular * specularTerm;

		// Final light colour
		vec3 finalColour = ambientColour + diffuseColour + specularColour;

		if (isTextured)
		
		{
			fragColour = vec4(finalColour, 1.0) * texture(textureImage, textureOut);
		}

		else
		{
			fragColour = vec4(finalColour, 1.0);
		}
	}

	else
	{
		fragColour = colourOut;
	}
}