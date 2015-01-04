#pragma once
#include "Model.h"
#include <string>
#include "ShaderProgram.h"

class ModelLoader
{
public:
	ModelLoader(void);
	~ModelLoader(void);

	Model * Load(std::string modelfile,ShaderProgram *,float scale);
};

