#version 150 

in vec3 out_vNormal;
in vec3 out_vLight;
in vec3 out_vEyeDirection;

out vec4 fragColor;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct, OriginalColor;
uniform float Shininess;

void main() 
{
	vec4 ambient, diffuse, specular;
	vec3 v3Normal_eye = normalize(out_vNormal);
	vec3 v3Light_eye = normalize(out_vLight);
	vec3 v3EyeDirection = normalize(out_vEyeDirection);

	vec3 v3HalfVector_eye = normalize(v3Light_eye + v3EyeDirection);
	
	float Kd = max(dot(v3Light_eye, v3Normal_eye),0.0);
	float Ks = pow(max(dot(v3Normal_eye, v3HalfVector_eye),0.0), Shininess);
	ambient = AmbientProduct;
	diffuse = Kd*DiffuseProduct;
	specular = max(Ks*SpecularProduct, 0.0);








	vec4 color = (ambient + diffuse + specular) * OriginalColor;
	//color = specular;
	color.w = OriginalColor.w;
 
    fragColor = color;
} 

