#pragma once
#include "AGameObject.h"
#include "Plane.h"
class PlaneObject : public AGameObject
{
public:
	PlaneObject(String name, VFShaders* shaders);
	~PlaneObject();

	virtual void initialize() override;
	virtual void update() override;
	virtual void draw() override;

private:
	Plane* plane;
	VFShaders* shaders;
};

