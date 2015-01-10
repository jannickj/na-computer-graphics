#include "Model.h"

Model::Model(GLuint vaoID, std::vector<int> meshindices, std::vector<vec3> normals, std::vector<vec2> uv, vec3 outerMax, vec3 outerMin)
{
	this->meshindices = meshindices;
	this->normals = normals;
	this->textureCord = uv;
	this->vaoID = vaoID;
	this->outerMax = outerMax;
	this->outerMin = outerMin;
}

void Model::Bind() const
{
	glBindVertexArray(this->vaoID);
}

void Model::Draw() const
{
	glDrawElements( GL_TRIANGLES, this->meshindices.size(), GL_UNSIGNED_INT, &this->meshindices[0]);
}

void Model::Release() const
{
	glBindVertexArray(this->vaoID);
}

std::vector<int> Model::getMeshindices() const
{
	return this->meshindices;
}

std::vector<vec3> Model::getNormals() const
{
	return this->normals;
}
	
std::vector<vec2> Model::getTextureCord() const
{
	return this->textureCord;
}

vec3 Model::getDimensions() const
{
	vec3 dim = this->outerMax - this->outerMin;
	return dim;
}

Model::~Model(void)
{
}
