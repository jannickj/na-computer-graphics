#include "ObjectDrawer.h"

using namespace std;

ObjectDrawer::ObjectDrawer(std::vector<NAObject*> objects)
{
	this->objects = objects;
}


ObjectDrawer::~ObjectDrawer(void)
{
}

void ObjectDrawer::draw(NAObject * nao)
{
	mat4 modelview = this->view*nao->getModel();
	ShaderProgram * shader = nao->getShader();

	GLuint modelviewPtr = shader->Get("ModelView");
	glUniformMatrix4fv( modelviewPtr, 1, GL_TRUE, modelview );

	GLuint projectPtr = shader->Get("Projection");
	glUniformMatrix4fv( projectPtr, 1, GL_TRUE, this->projection );

	cout << "drawing";

	nao->Draw();
}

void ObjectDrawer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	for (auto it = this->objects.begin(); it != this->objects.end(); ++it) {
		this->draw((*it));
	}

	glutSwapBuffers();
	Angel::CheckError();
}

void ObjectDrawer::SetView(mat4 view)
{
	this->view = view;
}

void ObjectDrawer::TransformView(mat4 trans)
{
	this->view = trans;
}

void ObjectDrawer::SetProject(mat4 project)
{
	this->projection = project;
}
