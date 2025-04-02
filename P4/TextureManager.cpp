#include "TextureManager.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void TextureManager::load(String name, const char* path, bool flipVert)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    this->textureMap[name] = textureID;

    this->load(path, flipVert, GL_TEXTURE_2D);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureManager::loadSkybox(String name, const char* directory)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    this->textureMap[name] = textureID;

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int i = 0;
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (std::filesystem::is_regular_file(entry.status()))
        {
            String path = entry.path().string();
            this->load(path.c_str(), false, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
            i++;
        }
    }
}

void TextureManager::load(const char* path, bool flipVert, GLenum target)
{
    stbi_set_flip_vertically_on_load(flipVert);

    int imgWidth;
    int imgHeight;
    int colorChannels;

    unsigned char* data = stbi_load(
        path,
        &imgWidth,
        &imgHeight,
        &colorChannels,
        0
    );

    int channels = 0;
    if (colorChannels == 3)
        channels = GL_RGB;
    else if (colorChannels > 3)
        channels = GL_RGBA;

    glTexImage2D(
        target,
        0,
        channels,
        imgWidth,
        imgHeight,
        0,
        channels,
        GL_UNSIGNED_BYTE,
        data
    );

    stbi_image_free(data);
}

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
    if (sharedInstance == NULL)
        sharedInstance = new TextureManager();

    return sharedInstance;
}

GLuint TextureManager::getTexture(String name)
{
    return this->textureMap[name];
}
