#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint TextureManager::load(const char* path, bool flipVert) {
    if (this->textureMap.find(path) != this->textureMap.end())
        return this->textureMap[path];

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

    glGenTextures(1, &this->textureMap[path]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureMap[path]);

    glTexImage2D(
        GL_TEXTURE_2D,
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
    glGenerateMipmap(GL_TEXTURE_2D);

    return this->textureMap[path];
}

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
    if (sharedInstance == NULL)
        sharedInstance = new TextureManager();

    return sharedInstance;
}