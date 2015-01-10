
#include "ObjectDrawer.h"
#include "ModelLoader.h"
#include <string>
#include "NAFactory.h"
#include "VoxelWorldBuilder.h"

using namespace std;

float screen_height;
float screen_width;
vec2 screen_mid;
float aspect = 1;
ObjectDrawer * drawer;
GLuint program;

float movespeed = 1;
float turnMax = 3;

ShaderProgram * loadShader()
{
	program = InitShader( "phong-shader.vert", "phong-shader.frag", "fragColor" );
	ShaderProgram * shader = new ShaderProgram(program);
	GLuint attPtr;
	string attStr;

	attStr = "vPosition";
	attPtr = glGetAttribLocation( program, attStr.c_str() );
	shader->loadAtt(attStr, attPtr);

	attStr = "vNormal";
	attPtr = glGetAttribLocation( program, attStr.c_str() );
	shader->loadAtt(attStr, attPtr);
	
	attStr = "ModelView";
	attPtr = glGetUniformLocation( program, attStr.c_str() );
	shader->loadAtt(attStr, attPtr);

	attStr = "Projection";
	attPtr = glGetUniformLocation( program, attStr.c_str() );
	shader->loadAtt(attStr, attPtr);

	shader->Use();
	return shader;
}

float maxSpeed(float max, float cur)
{
	if(cur > max)
		return max;
	else if(cur < -max)
		return -max;
	else
		return cur;
}

void motion(int x, int y)
{
	
	vec2 cursor = vec2(x, y);
	vec2 speed = cursor - screen_mid;
	/*if(speed.x != 0 && speed.y != 0)
		cout << "x: " << speed.x << ", y: " << speed.y << "\n";*/
	

	speed.x = maxSpeed(turnMax, speed.x);
	speed.y = maxSpeed(turnMax, speed.y);

	drawer->TransformView(RotateY(speed.x)*RotateX(speed.y));

	if(!(x == screen_mid.x && y == screen_mid.y))
		glutWarpPointer(screen_mid.x, screen_mid.y);
	
}

void mouse( int button, int state, int x, int y ) {

    if ( state == GLUT_DOWN ) {
		switch( button ) {
			case GLUT_LEFT_BUTTON:    
				break;
			case GLUT_RIGHT_BUTTON:
				
				break;
		}
    }
	//glfwSetMousePos(x,y);
}

void keyboard(unsigned char key, int x, int y) {
	
	switch (key){
		case '\033': 
			exit(0); 
			break;
		case 'w':
			drawer->TransformView(Translate(0,0,movespeed));
			break;
		case 's':
			drawer->TransformView(Translate(0,0,-movespeed));
			break;
		case 'a':
			drawer->TransformView(Translate(movespeed,0,0));
			break;
		case 'd':
			drawer->TransformView(Translate(-movespeed,0,0));
		case 'q':
			drawer->TransformView(RotateZ(-turnMax));
			break;
		case 'e':
			drawer->TransformView(RotateZ(turnMax));
			break;
	}
}


void reshape( int width, int height ) {
    glViewport( 0, 0, width, height );
	screen_height = height;
	screen_width = width;
    aspect = float(width)/height;
	screen_mid = vec2(screen_width / 2, screen_height / 2);
}

void display( void ) {
	

	// Initialize shader lighting parameters
    vec4 light_position( 0.0, 0.0, -1, 0.0 );
    vec4 light_ambient( 0.2, 0.2, 0.2, 1.0 );
    vec4 light_diffuse( 1.0, 1.0, 1.0, 1.0 );
    vec4 light_specular( 1.0, 1.0, 1.0, 1.0 );

    vec4 material_ambient( 1.0, 0.0, 1.0, 1.0 );
    vec4 material_diffuse( 1.0, 0.8, 0.0, 1.0 );
    vec4 material_specular( 1.0, 0.8, 0.0, 1.0 );
    float  material_shininess = 100.0;

    vec4 ambient_product = light_ambient * material_ambient;
    vec4 diffuse_product = light_diffuse * material_diffuse;
    vec4 specular_product = light_specular * material_specular;

    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"),
		  1, ambient_product );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"),
		  1, diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"),
		  1, specular_product );
	
    glUniform4fv( glGetUniformLocation(program, "LightPosition"),
		  1, light_position );

    glUniform1f( glGetUniformLocation(program, "Shininess"),
		 material_shininess );


	drawer->Draw();
	
	glutPostRedisplay();
}


int main(int argc, char* argv[]) 
{
	
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    
	glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_3_2_CORE_PROFILE);
	glutCreateWindow("02561-04-02");
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );
	glutMotionFunc( motion );
	//glutTimerFunc(10, animate, 0);
    //glutIdleFunc( idle );
	glutReshapeWindow(512, 512);

	Angel::InitOpenGL();


	ModelLoader * modelloader = new ModelLoader();

	ShaderProgram * shader = loadShader();

	Model * suzanne = modelloader->Load("suzanne.obj", shader, 0.5f);
	Model * sphere = modelloader->Load("sphere_hi-res.obj", shader, 0.5f);
	Model * cube = modelloader->Load("cube.obj", shader, 0.5f);

	vector<NAObject*> objects;

	NAObject * nao;

	//nao = new NAObject(shader, suzanne);
	//nao->SetModel(RotateZ(90)*Translate(0,-1,0)*Scale(0.2,0.2,0.2));
	//objects.push_back(nao);

	//nao = new NAObject(shader, suzanne);
	//nao->SetModel(Translate(0,1,0)*Scale(0.2,0.2,0.2));
	//objects.push_back(nao);

	//nao = new NAObject(shader, sphere);
	////nao->SetModel(Translate(0,1,0)*Scale(0.2,0.2,0.2));
	//objects.push_back(nao);

	drawer = new ObjectDrawer(objects);
	drawer->SetProject(Perspective( 45.0, aspect, 0.01, 10000.0 ));
	drawer->SetView(LookAt(vec4(10,5,12.0),vec4(0.0),vec4(0.0,1.0,0.0)));


	NAFactory * factory = new NAFactory(shader);

	VoxelWorldBuilder * wbuilder = new VoxelWorldBuilder(factory, cube, drawer);

	//wbuilder->AddVoxel(vec3(0,0,0));
	wbuilder->AddVoxel(vec3(0,1,0));
	wbuilder->AddVoxel(vec3(0,-1,0));
	wbuilder->AddVoxel(vec3(1,0,0));
	wbuilder->AddVoxel(vec3(-1,0,0));
	
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 



	Angel::CheckError();

    glutMainLoop();

}