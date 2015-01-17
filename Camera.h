#pragma once
#include <GL/freeglut.h>
#include <GL/glut.h>
#include "Utils.h"

class Camera
{
private:
    float posX;
    float posY;
    float posZ;
    float rotX;
    float rotY;
    float initPosX;
    float initPosY;
    float initPosZ;
    float initRotX;
    float initRotY;
	float initDistance;
    float mouseSpeed;
    float moveSpeed;
    float distance;
    double floorLvl;
    double roomSizeX;
    double roomSizeZ;
public:
    Camera(float posX, float posY, float posZ, float rotX, float rotY, double floorLvl, double roomSizeX, double roomSizeZ);
    ~Camera();
    void refresh();
    void handleKeyboard(unsigned char key);
    void handleMouseMoved(int button, int deltaX, int deltaY);
    double calcDistance(double x, double y, double z);
    void calcLimits();
    bool checkLimit();
    void reset();
};

