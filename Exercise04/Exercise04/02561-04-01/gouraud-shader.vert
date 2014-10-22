#version 150 

in  vec3 vPosition;//_world
in  vec3 vNormal;//_world
out vec4 color;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;//_world
uniform float Shininess;

void main()
{
    gl_Position = Projection * ModelView * vec4(vPosition, 1.0);



	vec4 vNormal_eye = normalize(ModelView * vec4(vNormal, 0.0));
	vec4 diffuse = DiffuseProduct * dot(vNormal_eye, normalize(LightPosition*-1.0));


	vec4 specular;

	//vec4 origin_eye = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 view_direction = normalize(ModelView * vec4(vPosition, 0.0)) * -1.0; //vNormal_eye - origin_eye;

	vec4 half = normalize((LightPosition) + view_direction) * -1.0;
	float s = dot(half, vNormal_eye);

	if ( s > 0.0) 
	{
		specular = pow(s, Shininess)*SpecularProduct;
	}
	else 
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}


    color = AmbientProduct+diffuse+specular;			
}
