#version 150

uniform sampler2D texture1;

uniform mat4 lightViewProjection;

out vec4 fragColor;

in vec2 vTextureCoordinate;

void main(void) {
	if (!gl_FrontFacing){
		fragColor = vec4(1,1,1,1);
		return;
	}

	vec4 vTextureCoordinate_light = lightViewProjection * vec4(vTextureCoordinate.x, vTextureCoordinate.y, 0, 0);

	vec2 shadowUV = normalize(vTextureCoordinate_light.xy / vTextureCoordinate_light.w); // todo find the shadow map UV coordinates

	fragColor = vec4(shadowUV.x, shadowUV.y,0.0,1.0);//texture(texture1, vTextureCoordinate);
}
