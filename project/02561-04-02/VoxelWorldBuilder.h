#pragma once
#include "Model.h"
#include "ObjectDrawer.h"
#include "Angel\Angel.h"
#include "NAFactory.h"

class VoxelWorldBuilder
{
private:
	Model * useModel;
	ObjectDrawer * drawer;
	NAFactory * factory;

public:
	VoxelWorldBuilder(NAFactory * factory, Model * useModel, ObjectDrawer * drawer);
	~VoxelWorldBuilder(void);
	void AddVoxel(vec3 cords, vec4 color);
};

