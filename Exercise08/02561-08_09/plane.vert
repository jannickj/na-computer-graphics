#version 150

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

in vec3 position;
in vec2 textureCoordinate;

out vec2 vTextureCoordinate;
out vec4 vWorld_pos;

void main(void)
{
	gl_Position = projection * view * model * vec4(position,1.0);
	
	vWorld_pos = model * vec4(position,1.0);
	
	vTextureCoordinate = textureCoordinate;
}