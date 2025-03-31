#pragma once
#include <string>
#include <unordered_map>
#include "VFShaders.h"

class ShaderManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, VFShaders*> HashTable;

    static ShaderManager* getInstance();
    bool load();

    VFShaders* getShaders();

private:
    ShaderManager() {}
    ShaderManager(const ShaderManager&) {}
    ShaderManager& operator = (const ShaderManager&) {}
    static ShaderManager* sharedInstance;

    HashTable shaderMap;
};
