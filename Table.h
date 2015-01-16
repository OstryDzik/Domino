#pragma once
#include "Drawable.h"
#include "Cuboid.h"
#include <vector>
class Table : public Drawable
{
private:
    double posX;
    double posY;
    double posZ;
    int sizeX;
    int sizeY;
    int sizeZ;
    int thickness;
    std::vector<Cuboid*> parts;
public:
    Table();
    Table(double posX, double posY, double posZ, int x, int y, int z, int thickness);
    ~Table();
    void draw();
};

