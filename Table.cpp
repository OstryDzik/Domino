#include "Table.h"
#include "TextureManager.h"

Table::Table(double posX, double posY, double posZ, int x, int y, int z, int thickness)
{
    parts.push_back(new Cuboid(posX, posY, posZ, thickness, y - thickness, thickness));
    parts.push_back(new Cuboid(posX + x - thickness, posY, posZ, thickness, y - thickness, thickness));
    parts.push_back(new Cuboid(posX, posY, posZ + z - thickness, thickness, y - thickness, thickness));
    parts.push_back(new Cuboid(posX + x - thickness, posY, posZ + z - thickness, thickness, y - thickness, thickness));
    parts.push_back(new Cuboid(posX, posY + y - thickness, posZ, x, thickness, z));
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->sizeX = x;
    this->sizeY = y;
    this->sizeZ = z;
    this->thickness = thickness;
    for (int i = 0; i < parts.size(); i++)
    {
        parts.at(i)->setAllTex(TexType::Wood);
    }
}


Table::~Table()
{
    for (int i = 0; i < parts.size(); i++)
    {
       delete parts.at(i);
    }
    parts.clear();
}

void Table::draw()
{
    for (int i = 0; i < parts.size(); i++)
    {
        parts.at(i)->draw();
    }
}