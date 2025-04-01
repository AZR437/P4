#pragma once
#include <string>
#include <unordered_map>
#include <glad/glad.h>

class TextureManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, GLuint> HashTable;

    static TextureManager* getInstance();
    GLuint load(const char* path, bool flipVert = false);
    GLuint loadSkybox(const char* directory);

private:
    TextureManager() {}
    TextureManager(const TextureManager&) {}
    TextureManager& operator = (const TextureManager&) {}
    static TextureManager* sharedInstance;

    HashTable textureMap;
};
