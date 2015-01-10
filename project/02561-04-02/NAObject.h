#pragma once
#include "Angel.h"
#include "Model.h"
#include "ShaderProgram.h"

class NAObject
{
private:
	mat4 model;
	Model * model3d;
	ShaderProgram * shader;
	vec4 color;

public:
	NAObject(ShaderProgram * shader, Model * Model3d);
	~NAObject(void);
	Model * NAObject::getModel3d() const;
	mat4 const& getModel() const;
	ShaderProgram * getShader() const;
	void Transform(mat4 trans);
	void SetModel(mat4 model);
	void Draw();
	void SetColor(vec4 color);
};

