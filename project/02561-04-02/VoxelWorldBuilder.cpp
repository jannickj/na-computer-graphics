#include "VoxelWorldBuilder.h"
#include "NAObject.h"


VoxelWorldBuilder::VoxelWorldBuilder(NAFactory * factory, Model * useModel, ObjectDrawer * drawer)
{
	this->useModel = useModel;
	this->drawer = drawer;
	this->factory = factory;
}


VoxelWorldBuilder::~VoxelWorldBuilder(void)
{
}

void VoxelWorldBuilder::AddVoxel(vec3 cords, vec4 color)
{
	NAObject * object = this->factory->CreateObject(this->useModel);
	object->SetColor(color);
	vec3 pos = cords * (this->useModel->getDimensions());
	
	object->Transform(Translate(pos));
	this->drawer->AddObject(object);

}