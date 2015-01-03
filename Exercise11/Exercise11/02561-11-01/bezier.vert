#version 150

uniform mat4 projection;
uniform mat4 modelView;
uniform mat4 curveMatrix;

in float u;

void main(void)
{
	vec4 position = vec4(1, u, u*u, u*u*u) * curveMatrix;//vec4(u*100, u*100, 0, 1);
	gl_Position = projection * modelView * position;
}