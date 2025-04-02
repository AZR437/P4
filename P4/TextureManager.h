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
    GLuint getTexture(String name);
    void load(String name, const char* path, bool flipVert = false);
    void loadSkybox(String name, const char* directory);

private:
    void load(const char* path, bool flipVert, GLenum target);

private:
    TextureManager() {}
    TextureManager(const TextureManager&) {}
    TextureManager& operator = (const TextureManager&) {}
    static TextureManager* sharedInstance;

    HashTable textureMap;
};
