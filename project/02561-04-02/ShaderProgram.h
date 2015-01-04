#pragma once

#include "Angel\Angel.h"
#include <map>
#include <string>

class ShaderProgram
{
private:
	GLuint program;
	std::map<std::string,GLuint> attmap;

public:
	ShaderProgram(GLuint program);
	~ShaderProgram(void);
	void loadAtt(std::string attr, GLuint ptr);
	GLuint Get(std::string attr);
	void ShaderProgram::Use();

};

