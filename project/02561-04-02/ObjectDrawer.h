#pragma once
#include "NAObject.h"
#include <vector>

class ObjectDrawer
{
private:
	std::vector<NAObject*> objects;
	mat4  projection;
	mat4 view;
	void draw(NAObject * nao);

public:
	ObjectDrawer(std::vector<NAObject*> objects);
	~ObjectDrawer(void);

	void Draw();

	void SetView(mat4);
	void SetProject(mat4);
	void TransformView(mat4 trans);

};

