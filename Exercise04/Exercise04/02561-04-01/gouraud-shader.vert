#version 150 

in  vec3 vPosition;//_world
in  vec3 vNormal;//_world
out vec4 color;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;//_eye
uniform float Shininess;

void main()
{
	vec4 vPosition_eye = ModelView * vec4(vPosition, 1.0);

    gl_Position = Projection * vPosition_eye;


	
	vec4 diffuse;
	vec4 vNormal_eye = normalize(ModelView*vec4(vNormal,0));
	float K_d = dot(vNormal_eye, normalize(LightPosition*-1.0));
	float d = dot(vNormal_eye, normalize(LightPosition));
	if (d > 0) 
		diffuse  = DiffuseProduct * K_d;
	else 
		diffuse = vec4(0.0, 0.0, 0.0, 1.0);


	vec4 specular;


	vec4 view_direction = -normalize(vPosition_eye); 

	vec4 L = LightPosition - vPosition_eye;

	vec4 half = -normalize(L + view_direction);
	half.w = 0;
	float s = dot(half, vNormal_eye);

	if ( s > 0.0) 
	{
		specular = pow(s, Shininess)*SpecularProduct;
	}
	else 
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}


    color = specular;			//AmbientProduct+diffuse+
}
