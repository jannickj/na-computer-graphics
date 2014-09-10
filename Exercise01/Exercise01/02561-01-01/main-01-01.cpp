// 02561-01-01 Hello triangle world

#include <iostream>
#include <string>


#include "Angel.h"

using namespace std;
using namespace Angel;

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

GLuint shaderProgram;
GLuint colorAttribute, positionAttribute;
GLuint vertexArrayObject;

struct Vertex{
	vec2 position;
	vec3 color;
};

const int NUMBER_OF_VERTICES = 6;
Vertex vertexData[NUMBER_OF_VERTICES] = {
	{ vec2(-0.5, -0.5 ), vec3( 1.0, 0.0, 0.0) },
	{ vec2( 0.5, -0.5 ), vec3( 0.0, 1.0, 0.0 ) },
	{ vec2( 0.5,  0.5 ), vec3( 0.0, 0.0, 1.0 ) },
	{ vec2(0.5, 0.5 ), vec3( 1.0, 1.0, 1.0) },
	{ vec2( -0.5, 0.5 ), vec3( 1.0, 1.0, 1.0 ) },
	{ vec2( -0.5,  -0.5 ), vec3( 1.0, 1.0, 1.0 ) }
};

// forward declaration
void loadShader();
void display();
void loadBufferData();
void reshape(int W, int H);


void display() {	
	glClearColor(0.0, 0.0, 0.0, 1.0);//sets background color (black)
	glClear(GL_COLOR_BUFFER_BIT);//buffer clearing
	
	glUseProgram(shaderProgram);//use the shader programs color-shader.freg and .vert

	glBindVertexArray(vertexArrayObject);
    
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NUMBER_OF_VERTICES); //defines which primites to use
	
	glutSwapBuffers();//swaps the buffer to avoid updating the buffer being used

	Angel::CheckError();
}

//handles resizing of the window
void reshape(int windowWidth, int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}

//handles OpenGL buffering
void loadBufferData() {
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	GLuint  vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_VERTICES * sizeof(Vertex), vertexData, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(positionAttribute);
	glEnableVertexAttribArray(colorAttribute);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)0);
	glVertexAttribPointer(colorAttribute  , 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)sizeof(vec2));
}

//setting the shaderProgram to the color-shader files
void loadShader() {
	shaderProgram = InitShader("color-shader.vert",  "color-shader.frag", "fragColor");
	colorAttribute = glGetAttribLocation(shaderProgram, "color");
	positionAttribute = glGetAttribLocation(shaderProgram, "position");
}

//inits various glut stuff
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextVersion(3, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_3_2_CORE_PROFILE);
	glutCreateWindow("02561-01-01");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	Angel::InitOpenGL();
		
	loadShader();
	loadBufferData();

	Angel::CheckError();
	glutMainLoop();
}