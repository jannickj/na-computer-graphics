#version 150

uniform sampler2D texture1;

uniform mat4 lightViewProjection;

uniform sampler2D ShadowMap;

out vec4 fragColor;

in vec2 vTextureCoordinate;
in vec4 vWorld_pos;

void main(void) {
	if (!gl_FrontFacing){
		fragColor = vec4(1,1,1,1);
		return;
	}

	vec4 normalizedDeviceCord = (lightViewProjection * vWorld_pos);
	vec2 shadowUV = normalizedDeviceCord.xy / normalizedDeviceCord.w;

	vec2 mappedToTex = (shadowUV + 1.0) / 2.0;

	vec4 sColor = texture(ShadowMap, mappedToTex);
	if (sColor.x == 0.0)
	{
		sColor.x = 0.5;
		sColor.y = 0.5;
		sColor.z = 0.5;
	}
	else
	{
		sColor.x = 1;
		sColor.y = 1;
		sColor.z = 1;
	}



	fragColor = texture(texture1, vTextureCoordinate) * sColor; //vec4(mappedToTex.xy,0.0,1.0);
}
