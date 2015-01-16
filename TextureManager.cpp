#define _CRT_SECURE_NO_DEPRECATE
#include "TextureManager.h"
#include <fstream>

TextureManager* TextureManager::instance = NULL;

TextureManager::TextureManager()
{
    textures.push_back(this->LoadTexture("OneTwo.bmp"));
    textures.push_back(this->LoadTexture("TwoThree.bmp"));
    textures.push_back(this->LoadTexture("ThreeFour.bmp"));
    textures.push_back(this->LoadTexture("OneOne.bmp"));
    textures.push_back(this->LoadTexture("Wood.bmp"));
    textures.push_back(this->LoadTexture("Wallpaper.bmp"));
    textures.push_back(this->LoadTexture("Floor.bmp"));
}


TextureManager::~TextureManager()
{
}

TextureManager* TextureManager::getInstance()
{
    if (instance==NULL)
    {
        instance = new TextureManager();
    }   
    return instance;
}


GLuint TextureManager::LoadTexture(const char* FilePath)
{

    GLuint texture=textures.size()+1;
    int width = 0;
    int height = 0;
    short BitsPerPixel = 0;
    std::vector<unsigned char> Pixels;

    std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
    if (!hFile.is_open()) return 0;

    hFile.seekg(0, std::ios::end);
    int Length = hFile.tellg();
    hFile.seekg(0, std::ios::beg);
    std::vector<unsigned char> FileInfo(Length);
    hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);

    if (FileInfo[0] != 'B' && FileInfo[1] != 'M')
    {
        hFile.close();
        return 0;
    }

    if (FileInfo[28] != 24 && FileInfo[28] != 32)
    {
        hFile.close();
        return 0;
    }

    BitsPerPixel = FileInfo[28];
    width = FileInfo[18] + (FileInfo[19] << 8);
    height = FileInfo[22] + (FileInfo[23] << 8);
    unsigned long int PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
    unsigned long int size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    Pixels.resize(size);

    hFile.seekg(PixelsOffset, std::ios::beg);
    hFile.read(reinterpret_cast<char*>(Pixels.data()), size);
    hFile.close();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, Pixels.data());

    return texture;
}

GLuint TextureManager::getTexture(TexType ID)
{
    return textures.at((int)ID);
}