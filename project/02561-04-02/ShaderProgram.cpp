#include "ShaderProgram.h"

using namespace std;

ShaderProgram::ShaderProgram(GLuint program)
{
	this->program = program;
}


ShaderProgram::~ShaderProgram(void)
{
}


void ShaderProgram::loadAtt(string attr, GLuint ptr)
{
	auto it = this->attmap.begin();
	this->attmap.insert(it, pair<string,GLuint>(attr,ptr));
}

GLuint ShaderProgram::Get(std::string attr)
{
	return this->attmap[attr];
}

void ShaderProgram::Use()
{
	glUseProgram( this->program );
}