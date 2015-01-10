#pragma once
#include <vector>
#include "Angel\Angel.h"

class Model
{
private:
	std::vector<int> meshindices;
	std::vector<vec3> normals;
	std::vector<vec2> textureCord;
	GLuint vaoID;
	vec3 outerMax;
	vec3 outerMin;

public:
	Model(GLuint vaoID, std::vector<int> meshindices,std::vector<vec3> normals,std::vector<vec2> textureCords, vec3 outerMax, vec3 outerMin);
	~Model(void);
	void Bind() const;
	void Release() const;
	void Model::Draw() const;
	std::vector<int> getMeshindices() const;
	std::vector<vec3> getNormals() const;
	std::vector<vec2> getTextureCord() const;
	vec3 getDimensions() const;

};

