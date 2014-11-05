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

	vec4 ambient, diffuse, specular;
	vec4 v4Position_eye = ModelView * vec4(vPosition, 1.0);
	gl_Position = Projection * v4Position_eye;
	vec3 v3Position_eye = new vec3(v4Position_eye.x, v4Position_eye.y, v4Position_eye.z);
	 
	vec4 v4Normal_eye = normalize(ModelView * vec4(vNormal, 0.0));
	vec3 v3Normal_eye = new vec3(v4Normal_eye.x, v4Normal_eye.y, v4Normal_eye.z);
	vec3 v3LightDirection_eye = normalize(new vec3(LightPosition.x, LightPosition.y, LightPosition.z) - v3Position_eye);
	vec3 v3EyeDirection = -normalize(v3Position_eye);
	vec3 v3HalfVector_eye = normalize(v3LightDirection_eye + v3EyeDirection);
	
	float Kd = max(dot(v3LightDirection_eye, v3Normal_eye),0.0);
	float Ks = pow(max(dot(v3Normal_eye, v3HalfVector_eye),0.0), Shininess);
	ambient = AmbientProduct;
	diffuse = Kd*DiffuseProduct;
	specular = max(Ks*SpecularProduct, 0.0);
	color = ambient + diffuse + specular;
	color.w = 1.0;
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	//vec4 vPosition_eye = ModelView * vec4(vPosition, 1.0);
    //gl_Position = Projection * vPosition_eye;


	
	//vec4 diffuse;
	//vec4 vNormal_eye = normalize(ModelView*vec4(vNormal,0));
	//float K_d = dot(vNormal_eye, normalize(LightPosition*-1.0));
	//float d = dot(vNormal_eye, normalize(LightPosition));
	//if (d > 0) 
		//diffuse  = DiffuseProduct * K_d;
	//else 
		//diffuse = vec4(0.0, 0.0, 0.0, 1.0);


	//vec4 specular;


	//vec4 view_direction = -normalize(vPosition_eye); 

	//vec4 L = LightPosition - vPosition_eye;

	//vec4 half = normalize(L + view_direction);
	//half.w = 0;
	//float s = dot(half, vNormal_eye);

	//if ( s > 0.0) 
	//{
		//specular = pow(s, Shininess)*SpecularProduct;
	//}
	//else 
	//{
		//specular = vec4(0.0, 0.0, 0.0, 1.0);
	//}


    //color = specular;			//AmbientProduct+diffuse+
}
