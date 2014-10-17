#version 150
// 02561-03-01

uniform mat4 projection;
uniform mat4 modelView;
uniform float blendValue;
uniform float normalExtrusion;

in vec3 position1;
in vec3 color1;
in vec3 normal1;
in vec3 position2;
in vec3 color2;
in vec3 normal2;

out vec3 colorV;

float formula(float b, float in1, float in2)
{
	return (1-b)*in1+b*in2;
}

void main (void) {
    colorV = vec3( formula(blendValue,color1.x,color2.x), formula(blendValue,color1.y,color2.y), formula(blendValue,color1.z,color2.z) );

	//vec3 norm = vec3( formula(normalExtrusion,normal1.x,normal2.x), formula(normalExtrusion,normal1.y,normal2.y), formula(normalExtrusion,normal1.z,normal2.z) );

	vec3 norm1 = vec3( normal1.x*normalExtrusion, normal1.y*normalExtrusion, normal1.z*normalExtrusion);
	vec3 norm2 = vec3( normal2.x*normalExtrusion, normal2.y*normalExtrusion, normal2.z*normalExtrusion);

	vec3 pos = vec3( formula(blendValue,position1.x+norm1.x,position2.x+norm2.x), formula(blendValue,position1.y+norm1.y,position2.y+norm2.y), formula(blendValue,position1.z+norm1.z,position2.z+norm2.z) );

	//vec3 pos = vec3( formula(blendValue,position1.x,position2.x), formula(blendValue,position1.y,position2.y), formula(blendValue,position1.z,position2.z) );

    gl_Position = projection * modelView * vec4(pos, 1.0);
}