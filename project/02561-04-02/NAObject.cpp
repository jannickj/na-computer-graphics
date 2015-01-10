#include "NAObject.h"


NAObject::NAObject(ShaderProgram * shader, Model * vertexModel)
{
	this->color = vec4(1.0f);
	this->model3d = vertexModel;
	this->shader = shader;
}

Model * NAObject::getModel3d() const
{
	return this->model3d;
}

mat4 const& NAObject::getModel() const
{
	return this->model;
}

NAObject::~NAObject(void)
{
}

ShaderProgram * NAObject::getShader() const
{
	return this->shader;
}

void NAObject::Transform(mat4 trans)
{
	this->model = trans * this->model ;
}

void NAObject::SetModel(mat4 newModel)
{
	this->model = newModel;

}

void NAObject::Draw()
{
	//glColor4f(this->color.x,this->color.y,this->color.z,this->color.w);
	GLuint colorPtr = shader->Get("OriginalColor");
	glUniform4fv( colorPtr, 1, this->color );
	model3d->Bind();
	model3d->Draw();
	model3d->Release();
}

void NAObject::SetColor(vec4 color)
{
	this->color = color;
}
