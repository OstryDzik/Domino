#pragma once
#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <vector>

enum TexType
{
   NoTex = -1, OneDot, TwoDot, ThreeDot, FourDot, Wood, Wall,Floor
};

class TextureManager
{
private:
    static TextureManager* instance;
    TextureManager();
    std::vector<GLuint> textures;
public:
    ~TextureManager();
    static TextureManager* getInstance();
    GLuint getTexture(TexType ID);
    GLuint LoadTexture(const char* FilePath);
};

