#include "NAFactory.h"


NAFactory::NAFactory(ShaderProgram * shader)
{
	this->shader = shader;
}


NAFactory::~NAFactory(void)
{
}

NAObject * NAFactory::CreateObject(Model * model)
{
	return new NAObject(this->shader, model);
}
