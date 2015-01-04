
#include "ObjectDrawer.h"
#include "ModelLoader.h"
#include <string>

using namespace std;

float aspect = 1;
ObjectDrawer * drawer;
GLuint program;


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



void reshape( int width, int height ) {
    glViewport( 0, 0, width, height );

    aspect = float(width)/height;
}

void display( void ) {
	
	drawer->SetProject(Perspective( 45.0, aspect, 0.5, 3.0 ));
	drawer->SetView(LookAt(vec4(2.0,2.0,2.0),vec4(0.0),vec4(0.0,1.0,0.0)));

	// Initialize shader lighting parameters
    vec4 light_position( 0.0, 0.0, -1.0, 0.0 );
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
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutReshapeWindow(512, 512);

	Angel::InitOpenGL();


	ModelLoader * modelloader = new ModelLoader();

	ShaderProgram * shader = loadShader();

	Model * suzanne = modelloader->Load("suzanne.obj", shader, 0.5f);
	Model * sphere = modelloader->Load("sphere_hi-res.obj", shader, 0.5f);

	vector<NAObject*> objects;

	NAObject * nao;

	nao = new NAObject(shader, suzanne);
	nao->SetModel(RotateZ(90)*Translate(0,-1,0)*Scale(0.2,0.2,0.2));
	objects.push_back(nao);

	nao = new NAObject(shader, suzanne);
	nao->SetModel(Translate(0,1,0)*Scale(0.2,0.2,0.2));
	objects.push_back(nao);

	nao = new NAObject(shader, sphere);
	//nao->SetModel(Translate(0,1,0)*Scale(0.2,0.2,0.2));
	objects.push_back(nao);

	drawer = new ObjectDrawer(objects);


	
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 

    glutDisplayFunc( display );
    //glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );
    //glutMouseFunc( mouse );
    //glutIdleFunc( idle );

	Angel::CheckError();

    glutMainLoop();

}