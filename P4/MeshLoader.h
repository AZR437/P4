#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class MeshLoader
{
public:
	typedef std::string String;
	static bool load(const char* path, std::vector<GLfloat>* vertexData);
	static bool load(String data, std::vector<GLfloat>* vertexData);

private:

};

