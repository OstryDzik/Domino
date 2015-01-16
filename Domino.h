#pragma once
#include "Cuboid.h"
#include "Utils.h"


class Domino : public Cuboid 
{
private:
    double normal;
    double tilt;
    double contactTilt;
    bool resting;
public:
    Domino(double posX, double posY, double posZ, int sizeX, int sizeY, int sizeZ, double normal = 0);
    ~Domino();
    void draw();
    void step(double angle);
    void setTilt(double tilt);
    double getTilt();
    void reset();
    bool isResting();
};

