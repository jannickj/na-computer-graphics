#version 150

uniform samplerCube cubemap;

in vec3 vPosition;

out vec4 fragColor;

void main(void)
{
	

	
	vec3 v = vec3(1);

	fragColor = texture(cubemap,vPosition); //vec4(1.0,0.5,1.0,1.0);
}
