#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Light;
class VFShaders
{
private:
    GLuint shaderProgram;

public:
    VFShaders(std::string vertPath, std::string fragPath);

public:
    void setBool(const GLchar* varName, bool b);
    void setFloat(const GLchar* varName, float f);
    void setVec3(const GLchar* varName, glm::vec3 v3);
    void setMat4(const GLchar* varName, glm::mat4 m4);
    void setTexture(const GLchar* varName, GLuint* texture, GLenum active, GLenum type, GLint unit);
    void setLights(std::vector<Light*>& lights);

private:
    void createShader(std::string path, GLenum shaderType);

public:
    GLuint& getShaderProgram();
};
