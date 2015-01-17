#include "Camera.h"
#include <math.h>
#define MIN_DISTANCE 30

Camera::Camera(float posX, float posY, float posZ, float rotX, float rotY, double floorLvl, double roomSizeX, double roomSizeZ)
{
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->rotX = rotX;
    this->rotY = rotY;
    this->initPosX = posX;
    this->initPosY = posY;
    this->initPosZ = posZ;
    this->initRotX = rotX;
    this->initRotY = rotY;
    this->mouseSpeed = 0.5;
    this->moveSpeed = 4;
    this->floorLvl = floorLvl;
    this->roomSizeX = roomSizeX;
    this->roomSizeZ = roomSizeZ;
	initDistance = calcDistance(posX, posY, posZ);
}


Camera::~Camera()
{
}

void Camera::refresh()
{
    glLoadIdentity();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotY, 1, 0, 0);
    glRotatef(rotX, 0, 1, 0);
}

void Camera::handleMouseMoved(int button, int deltaX, int deltaY)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        rotX += (deltaX * mouseSpeed);
        if (rotY + deltaY * mouseSpeed > 0 && rotY + deltaY * mouseSpeed < 180)
        {
            rotY += (deltaY * mouseSpeed);

        }
    }
    else
    {
		if (calcDistance(posX, posY, posZ - (deltaY*mouseSpeed)) <= initDistance && calcDistance(posX, posY, posZ - (deltaY*mouseSpeed)) > MIN_DISTANCE)
		{
			posZ -= deltaY * mouseSpeed;
		}
    }
    calcLimits();
}

void Camera::handleKeyboard(unsigned char key)
{
    if (key == 'w')
    {
        posY-=moveSpeed;
    }

    else if (key == 's')
    {
        posY+=moveSpeed;
    }

    else if (key == 'd')
    {
        posX -= moveSpeed;
    }

    else if (key == 'a')
    {
        posX += moveSpeed;
    }
    else if (key == 'r')
    {
        reset();
    }
}

void Camera::calcLimits()
{
    this->distance = calcDistance(posX, posY, posZ);
}

double Camera::calcDistance(double x, double y, double z)
{
    return sqrt(x*x + y*y + z*z);
}

void Camera::reset()
{
    this->posX = initPosX;
    this->posY = initPosY;
    this->posZ = initPosZ;
    this->rotX = initRotX;
    this->rotY = initRotY;
}