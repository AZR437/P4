#include "VFShaders.h"
#include "DirLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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

void VFShaders::setLights(std::vector<Light*>& lights)
{
    for (auto light : lights)
    {
        std::string lightPos = light->getType() + ".position";

        std::string diffCol = light->getType() + ".diffuseCol";
        std::string ambiCol = light->getType() + ".ambientCol";
        std::string specCol = light->getType() + ".specularCol";

        std::string ambiStr = light->getType() + ".ambientStr";
        std::string specStr = light->getType() + ".specularStr";

        std::string shine = light->getType() + ".shininess";

        this->setVec3(lightPos.c_str(), light->getPosition());
        this->setVec3(diffCol.c_str(), light->getDiffuseCol());
        this->setVec3(ambiCol.c_str(), light->getAmbientCol());
        this->setVec3(specCol.c_str(), light->getSpecularCol());

        this->setFloat(ambiStr.c_str(), light->getAmbientStr());
        this->setFloat(specStr.c_str(), light->getSpecularStr());

        this->setFloat(shine.c_str(), light->getShininess());

        if (light->getType() == "PLight")
        {
            PointLight* PLight = (PointLight*)light;
            std::string con = light->getType() + ".con";
            std::string lin = light->getType() + ".lin";
            std::string quad = light->getType() + ".quad";

            this->setFloat(con.c_str(), PLight->getConstant());
            this->setFloat(lin.c_str(), PLight->getLinear());
            this->setFloat(quad.c_str(), PLight->getQuadratic());
        }
    }
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