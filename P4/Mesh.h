#pragma once
#include "VAO.h"
#include "VBO.h"
#include "VFShaders.h"

class Mesh
{
public:
	Mesh(VAO* vao, std::vector<GLfloat> vertices);
	~Mesh();
	void draw();

private:
	unsigned int numVertices = 0;
	VAO* vao;
	VBO* vbo;
	VFShaders* Shaders;
	GLuint* texture;
	GLuint* normalMap;
};

