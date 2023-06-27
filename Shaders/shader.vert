#version 400

in vec3 vertexIn;
in vec4 colourIn;
in vec2 textureIn;
in vec3 normalIn;

out vec3 vertexOut;
out vec4 colourOut;
out vec2 textureOut;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	colourOut = colourIn;
	textureOut = textureIn;

	normalOut = normalIn;

	vertexOut = (model * vec4(vertexIn, 1.0f)).xyz;

	gl_Position = projection * view * model * vec4(vertexIn, 1.0);		
	
	// Multiplying projection with view results in 3D camera.
	// Mouliplying view with model results in camera movements.
	// Multiplying model with vec4 results in changes from local space to world space.
}