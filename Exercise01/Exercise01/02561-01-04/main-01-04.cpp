// 02561-01-04

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Angel.h"

using namespace std;
using namespace Angel;

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

GLuint shaderProgram;
GLuint projectionUniform,
	modelViewUniform;
GLuint positionAttribute;
GLuint vertexArrayObject;

struct Vertex {
	vec2 position;
};

const int NUMBER_OF_VERTICES = 3;
Vertex vertexData[NUMBER_OF_VERTICES] = {
	{ vec2(0.0, 0.0 ) },
	{ vec2(0.5, 0.0 ) },
	{ vec2( 0.5, 0.1 ) }
};

// forward declaration
void loadShader();
void drawCircle_JA();
void display();
void loadBufferData();
void reshape(int W, int H);


void display() {	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(shaderProgram);

	mat4 projection = Ortho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(projectionUniform, 1, GL_TRUE, projection);	
	

	drawCircle_JA();
		
	glutSwapBuffers();

	Angel::CheckError();
}

void drawCircle_JA()
{
	int resolution = 360/atanf(0.1/0.5);
	int i;
	float triangleSize = 1;
	float rotateAngle = atanf(0.1/0.5);
	mat4 modelView;   
	glBindVertexArray(vertexArrayObject);

	printf("calc'ed resolution is: %d.\n", resolution);
	

	for (i = 0; i < resolution; i++)
	{		
		modelView = RotateZ(rotateAngle*i)*Scale(1,triangleSize,1);
		glUniformMatrix4fv(modelViewUniform, 1, GL_TRUE, modelView);
		glDrawArrays(GL_TRIANGLE_FAN, 0, NUMBER_OF_VERTICES);
	}
	
}

void reshape(int W, int H) {
	WINDOW_WIDTH = W;
	WINDOW_HEIGHT = H;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void loadBufferData() {
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	GLuint  vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, NUMBER_OF_VERTICES * sizeof(Vertex), vertexData, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(positionAttribute);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)0);
}

void loadShader() {
	shaderProgram = InitShader("const-shader.vert",  "const-shader.frag", "fragColor");
	projectionUniform = glGetUniformLocation(shaderProgram, "projection");
	if (projectionUniform == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'projection' uniform."<<endl;
	}
	modelViewUniform = glGetUniformLocation(shaderProgram, "modelView");
	if (modelViewUniform == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'modelView' uniform."<<endl;
	}
	positionAttribute = glGetAttribLocation(shaderProgram, "position");
	if (positionAttribute == GL_INVALID_INDEX) {
		cerr << "Shader did not contain the 'position' attribute." << endl;
	}
}

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
	glutCreateWindow("02561-01-04");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	Angel::InitOpenGL();
	
	loadShader();
	loadBufferData();

	Angel::CheckError();

	glutMainLoop();
}