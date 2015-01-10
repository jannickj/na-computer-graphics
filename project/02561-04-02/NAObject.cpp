#include "NAObject.h"


NAObject::NAObject(ShaderProgram * shader, Model * vertexModel)
{
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
	model3d->Bind();
	model3d->Draw();
	model3d->Release();
}