#pragma once
#include "AGameObject.h"
#include "Mesh.h"
#include "VFShaders.h"
class MeshObject : public AGameObject
{
public:
	MeshObject(String name, Mesh* mesh, VFShaders* shaders, GLuint* texture, GLuint* normalMap = NULL);
	~MeshObject();

	virtual void initialize() override;
	virtual void update() override;
	virtual void draw() override;

private:


private:
	Mesh* mesh;
	VFShaders* shaders;
	GLuint* texture;
	GLuint* normalMap;
};

