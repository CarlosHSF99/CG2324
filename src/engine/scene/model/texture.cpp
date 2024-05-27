#include <IL/il.h>
#include "engine/scene/model/texture.h"

Texture::Texture(tinyxml2::XMLElement *textureElement)
{
    const char *textureFilename = textureElement->Attribute("file");

    ILuint t;
    ILint tw, th;
    unsigned char *texData;
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) textureFilename);
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind() const
{
    if (id != 0) {
        glBindTexture(GL_TEXTURE_2D, id);
    }
}
