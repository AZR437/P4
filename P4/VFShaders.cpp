#include "VFShaders.h"

VFShaders::VFShaders(std::string vertPath, std::string fragPath) {
    this->shaderProgram = glCreateProgram();

    createShader(vertPath, GL_VERTEX_SHADER);
    createShader(fragPath, GL_FRAGMENT_SHADER);

    glLinkProgram(this->shaderProgram);
}

void VFShaders::setBool(const GLchar* varName, bool b) {
    glUseProgram(this->shaderProgram);
    GLuint boolLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform1i(boolLoc, b);
}

void VFShaders::setFloat(const GLchar* varName, float f) {
    glUseProgram(this->shaderProgram);
    GLuint floatLoc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform1f(floatLoc, f);
}

void VFShaders::setVec3(const GLchar* varName, glm::vec3 v3) {
    glUseProgram(this->shaderProgram);
    GLuint vec3Loc = glGetUniformLocation(this->shaderProgram, varName);
    glUniform3fv(vec3Loc, 1, glm::value_ptr(v3));
}

void VFShaders::setMat4(const GLchar* varName, glm::mat4 m4) {
    glUseProgram(this->shaderProgram);
    GLuint mat4Loc = glGetUniformLocation(this->shaderProgram, varName);
    glUniformMatrix4fv(mat4Loc, 1, GL_FALSE, glm::value_ptr(m4));
}

void VFShaders::setTexture(const GLchar* varName, GLuint* texture, GLenum active, GLenum type, GLint unit) {
    glUseProgram(this->shaderProgram);
    GLuint textureLoc = glGetUniformLocation(this->shaderProgram, varName);
    glActiveTexture(active);
    glBindTexture(type, *texture);
    glUniform1i(textureLoc, unit);
}

void VFShaders::createShader(std::string path, GLenum shaderType) {
    std::fstream source(path);
    std::stringstream buff;
    buff << source.rdbuf();
    std::string str = buff.str();
    const char* c = str.c_str();

    GLuint newShader = glCreateShader(shaderType);
    glShaderSource(newShader, 1, &c, NULL);
    glCompileShader(newShader);

    glAttachShader(this->shaderProgram, newShader);
}

GLuint& VFShaders::getShaderProgram() {
    return this->shaderProgram;
}