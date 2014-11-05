#version 150 

in vec3 out_vNormal;
in vec3 out_vLight[3];
in vec3 out_vEyeDirection;

out vec4 fragColor;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform float Shininess;

vec4 calcLight(vec3 v3Normal_eye, vec3 v3EyeDirection, vec3 vLight)
{
	vec4 diffuse, specular;
	vec3 v3Light_eye = vLight;

	vec3 v3HalfVector_eye = normalize(v3Light_eye + v3EyeDirection);
	
	float Kd = max(dot(v3Light_eye, v3Normal_eye),0.0);
	float Ks = pow(max(dot(v3Normal_eye, v3HalfVector_eye),0.0), Shininess);
	diffuse = Kd*DiffuseProduct;
	specular = max(Ks*SpecularProduct, 0.0);

	return diffuse+specular;
}

void main() 
{
	vec4 ambient;
	vec3 v3Normal_eye = normalize(out_vNormal);
	vec3 v3EyeDirection = normalize(out_vEyeDirection);	
	ambient = AmbientProduct;

	vec4 color = ambient;
	int i;
	for(i = 0; i < 3; i++)
		color += calcLight(v3Normal_eye, v3EyeDirection, out_vLight[i]);






	
	//color = specular;
	color.w = 1.0;
 

    fragColor = color;
} 



