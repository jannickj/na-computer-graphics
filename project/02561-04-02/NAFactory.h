#pragma once
#include "NAObject.h"

class NAFactory
{
private:
	ShaderProgram * shader;

public:
	NAFactory(ShaderProgram * shader);
	~NAFactory(void);
	NAObject * CreateObject(Model * model);
};

