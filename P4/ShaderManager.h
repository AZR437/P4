#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include "VFShaders.h"

class ShaderManager
{
public:
    typedef std::string String;
    typedef std::unordered_map<String, VFShaders*> HashTable;

    static ShaderManager* getInstance();
    void load(String name, String vertPath, String fragPath);
    void loadAll();

    VFShaders* getShaders(String name);

private:
    ShaderManager() {}
    ShaderManager(const ShaderManager&) {}
    ShaderManager& operator = (const ShaderManager&) {}
    static ShaderManager* sharedInstance;

    HashTable shaderMap;
};
