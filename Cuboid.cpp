#include "Cuboid.h"


Cuboid::Cuboid(double posX, double posY, double posZ, int sizeX, int sizeY, int sizeZ)
{
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sizeZ = sizeZ;
    this->reverse = 1;
    frontTex = TexType::NoTex;
    backTex = TexType::NoTex;
    sideTex = TexType::NoTex;
    botTex = TexType::NoTex;
}


Cuboid::~Cuboid()
{
}

void Cuboid::draw()
{
    glPushMatrix();
    if (botTex != TexType::NoTex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::getInstance()->getTexture(botTex));
    }
    glBegin(GL_QUADS); //bot
        glNormal3f(0.0f, -1.0f*reverse, 0.0f);
        glTexCoord2f(0, 0);
        glVertex3f(posX, posY, posZ);
        glTexCoord2f(0, 1);
        glVertex3f(posX, posY, posZ + sizeZ);
        glTexCoord2f(1, 1);
        glVertex3f(posX + sizeX, posY, posZ + sizeZ);
        glTexCoord2f(1, 0);
        glVertex3f(posX + sizeX, posY, posZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if (sideTex != TexType::NoTex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::getInstance()->getTexture(sideTex));
    }
    glBegin(GL_QUADS); //top
        glNormal3f(0.0f, 1.0f*reverse, 0.0f);
        glTexCoord2f(1, 0);
        glVertex3f(posX + sizeX, posY + sizeY, posZ);
        glTexCoord2f(0, 0);
        glVertex3f(posX, posY + sizeY, posZ);
        glTexCoord2f(0, 1);
        glVertex3f(posX, posY + sizeY, posZ + sizeZ);
        glTexCoord2f(1, 1);
        glVertex3f(posX + sizeX, posY + sizeY, posZ + sizeZ);
    glEnd();
    glBegin(GL_QUADS); //left
        glNormal3f(-1.0f*reverse, 0.0f, 0.0f);
        glTexCoord2f(1, 1);
        glVertex3f(posX, posY + sizeY, posZ + sizeZ);
        glTexCoord2f(0, 1);
        glVertex3f(posX, posY + sizeY, posZ);
        glTexCoord2f(0, 0);
        glVertex3f(posX, posY, posZ);
        glTexCoord2f(1, 0);
        glVertex3f(posX, posY, posZ + sizeZ);
    glEnd();
    glBegin(GL_QUADS); //right
        glNormal3f(1.0f*reverse, 0.0f, 0.0f);
        glTexCoord2f(0, 1);
        glVertex3f(posX + sizeX, posY + sizeY, posZ + sizeZ);
        glTexCoord2f(0, 0);
        glVertex3f(posX + sizeX, posY + sizeY, posZ);
        glTexCoord2f(1, 0);
        glVertex3f(posX + sizeX, posY, posZ);
        glTexCoord2f(1, 1);
        glVertex3f(posX + sizeX, posY, posZ + sizeZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    if (frontTex != TexType::NoTex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::getInstance()->getTexture(frontTex));
    } 
    glBegin(GL_QUADS); //front
        glNormal3f(0.0f, 0.0f, 1.0f*reverse);
        glTexCoord2f(1, 1);
        glVertex3f(posX + sizeX, posY + sizeY, posZ + sizeZ);
        glTexCoord2f(0, 1);
        glVertex3f(posX, posY + sizeY, posZ + sizeZ);
        glTexCoord2f(0, 0);
        glVertex3f(posX, posY, posZ + sizeZ);
        glTexCoord2f(1, 0);
        glVertex3f(posX + sizeX, posY, posZ + sizeZ);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    if (backTex != TexType::NoTex)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::getInstance()->getTexture(backTex));
    }
    glBegin(GL_QUADS); //back
        glNormal3f(0.0f, 0.0f, -1.0f*reverse);
        glTexCoord2f(1, 1);
        glVertex3f(posX + sizeX, posY + sizeY, posZ);
        glTexCoord2f(0, 1);
        glVertex3f(posX, posY + sizeY, posZ);
        glTexCoord2f(0, 0);
        glVertex3f(posX, posY, posZ);
        glTexCoord2f(1, 0);
        glVertex3f(posX + sizeX, posY, posZ);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Cuboid::revert()
{
    this->reverse *= -1;
}

void Cuboid::setSideTex(TexType ID)
{
    sideTex = ID;
}

void Cuboid::setFrontTex(TexType ID)
{
    frontTex = ID;
}

void Cuboid::setBackTex(TexType ID)
{
    backTex = ID;
}

void Cuboid::setBotTex(TexType ID)
{
    botTex = ID;
}

void Cuboid::setAllTex(TexType ID)
{
    sideTex = ID;
    backTex = ID;
    frontTex = ID;
    botTex = ID;
}