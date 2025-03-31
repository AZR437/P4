#include "ShaderManager.h"

ShaderManager* ShaderManager::sharedInstance = NULL;

ShaderManager* ShaderManager::getInstance()
{
    if (sharedInstance == NULL)
        sharedInstance = new ShaderManager();

    return sharedInstance;
}
