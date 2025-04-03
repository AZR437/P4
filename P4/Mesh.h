#pragma once
#include "VAO.h"
#include "VBO.h"

class Mesh
{
public:
	Mesh(std::vector<GLfloat> vertices);
	~Mesh();
	void bind();
	void draw();

private:
	unsigned int numVertices = 0;
	VAO* vao;
	VBO* vbo;
};

