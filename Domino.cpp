#include "Domino.h"
#include <ctime>


Domino::Domino(double posX, double posY, double posZ, int sizeX, int sizeY, int sizeZ, double normal) :
    Cuboid(posX, posY, posZ, sizeX, sizeY, sizeZ) 
{
    this->normal = normal;
    this->tilt = 0;
    resting = false;
    this->setFrontTex((TexType)(rand() % 4 ));
    this->setBackTex((TexType)(rand() % 4 ));
}


Domino::~Domino()
{
}

void Domino::draw()
{
    float tiltInAngles = tilt * 180 / M_PI;
    float normalInAngles = normal * 180 / M_PI;
    glPushMatrix();
        glTranslatef(posX, posY, posZ);
        glRotatef(normal, 0, 1, 0);
        glTranslatef(sizeX/2, 0, sizeZ/2);
        glRotatef(tilt, -1, 0, 0);
        glTranslatef(-sizeX / 2, 0, -sizeZ / 2);
        glTranslatef(-posX, -posY, -posZ);
        Cuboid::draw();
    glPopMatrix();
}

void Domino::step(double angle)
{
    if (tilt+angle<90)
    {
        setTilt(tilt +angle);
    }
    else
    {
        setTilt(90);
    }
}

double Domino::getTilt()
{
    return tilt;
}

void Domino::setTilt(double tilt)
{
    this->tilt = tilt;
    if (tilt == 90)
    {
        resting = true;
    }
}

void Domino::reset()
{
    tilt = 0;
    contactTilt = 0;
    resting = false;
}

bool Domino::isResting()
{
    return resting;
}

