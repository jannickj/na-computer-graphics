#version 150

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

in vec3 position;
in vec2 textureCoordinate;

out vec2 vTextureCoordinate;

void main(void)
{
	gl_Position = projection * view * model * vec4(position,1.0);
	
	vec4 vTextureCoordinate_world = projection * vec4(textureCoordinate.x, textureCoordinate.y, 0, 0);

	vTextureCoordinate = vTextureCoordinate_world.xy;
}