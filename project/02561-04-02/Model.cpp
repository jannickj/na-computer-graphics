#include "Model.h"


Model::Model(GLuint vaoID, std::vector<int> meshindices, std::vector<vec3> normals, std::vector<vec2> uv)
{
	this->meshindices = meshindices;
	this->normals = normals;
	this->textureCord = uv;
	this->vaoID = vaoID;

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

Model::~Model(void)
{
}
