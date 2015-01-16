#pragma once
#include <GL/freeglut.h>
#include <GL/glut.h>
#include "Drawable.h"
#include "TextureManager.h"

class Cuboid : public Drawable
{
protected:
    double posX;
    double posY;
    double posZ;
    int sizeX;
    int sizeY;
    int sizeZ;
    float reverse;
    TexType frontTex;
    TexType backTex;
    TexType sideTex;
    TexType botTex;
public:
    Cuboid(double posX, double posY, double posZ, int sizeX, int sizeY, int sizeZ);
    ~Cuboid();
    void draw();
    void revert(); //cahanges display from outside to iside
    void setSideTex(TexType ID);
    void setFrontTex(TexType ID);
    void setBackTex(TexType ID);
    void setAllTex(TexType ID);
    void setBotTex(TexType ID);
};

