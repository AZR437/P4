#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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
	EBO* ebo;
};

