#include "ShaderManager.h"
#include <filesystem>
#include "StringUtils.h"

ShaderManager* ShaderManager::sharedInstance = NULL;

ShaderManager* ShaderManager::getInstance()
{
    if (sharedInstance == NULL)
        sharedInstance = new ShaderManager();

    return sharedInstance;
}

void ShaderManager::load(String name, String vertPath, String fragPath)
{
    this->shaderMap[name] = new VFShaders(vertPath, fragPath);
}

void ShaderManager::loadAll()
{

    //for (const auto& entry : std::filesystem::directory_iterator("Shaders"))
    //{
    //    if (std::filesystem::is_regular_file(entry.status()))
    //    {
    //        std::vector<String> tokens = StringUtils::split(entry.path().string(), '/');
    //        std::vector<String> fileName = StringUtils::split(tokens[tokens.size() - 1], '.');
    //        String name = fileName[0];
    //        String type = fileName[1];
    //        
    //    }
    //}

    //this->shaderMap[name] = new VFShaders(entry.path().string(), entry.path().string());
}

VFShaders* ShaderManager::getShaders(String name)
{
    
    return nullptr;
}
