#version 150 

in  vec3 vPosition;
in  vec3 vNormal;

out vec3 out_vNormal;
out vec3 out_vLight;
out vec3 out_vEyeDirection;


uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;

void main()
{
	vec4 v4Position_eye = ModelView * vec4(vPosition, 1.0);
	gl_Position = Projection * v4Position_eye;
	vec3 v3Position_eye = new vec3(v4Position_eye.x, v4Position_eye.y, v4Position_eye.z);
	 
	vec4 v4Normal_eye = ModelView * vec4(vNormal, 0.0);
	out_vNormal = new vec3(v4Normal_eye.x, v4Normal_eye.y, v4Normal_eye.z);

	vec4 modified_LightPosition = ModelView * LightPosition; //use?

	if (LightPosition.w == 0.0) 
		out_vLight = -new vec3(LightPosition.x, LightPosition.y, LightPosition.z);
	else 
		out_vLight = new vec3(LightPosition.x, LightPosition.y, LightPosition.z) - v3Position_eye;

	out_vEyeDirection = -v3Position_eye;

    
}
