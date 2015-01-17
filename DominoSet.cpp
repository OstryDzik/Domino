#include "DominoSet.h"
#include <math.h>


DominoSet::DominoSet(int count)
{
    started = false;
    ready = false;
    paused = false;
    actualDomino = 0;
    defStepAngle = 1;
    defSizeX = 10;
    defSizeY = 20;
    defSizeZ = 2;
    defDistance = 6;
    loadDefaultSet(count);
}


DominoSet::~DominoSet()
{
    this->clear();
}


void DominoSet::loadDefaultSet(int count)
{
    this->clear();
    double startPos = count / 2 * (defSizeZ+defDistance);
    for (int i = 0; i < count; i++)
    {
        dominos.push_back(new Domino(0, 0, startPos-i*(defSizeZ+(defDistance)), defSizeX, defSizeY, defSizeZ));
    }
    started = false;
    ready = true;
    calcAngles();
}

void DominoSet::loadYSet(int count)
{
    this->clear();
    double startPos = count / 3 * (defSizeZ + defDistance);
    for (int i = 0; i < count/3; i++)
    {
        dominos.push_back(new Domino(0, 0, startPos - i*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
    }
    for (int i = 1; i <= count / 3; i++)
    {
        dominos.push_back(new Domino(i*defSizeX/2, 0, -(i-1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
        dominos.push_back(new Domino(-i*defSizeX / 2, 0, -(i-1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
    }
    started = false;
    ready = true;
    calcAngles();
}

void DominoSet::loadDiamondSet(int count)
{
	this->clear();
	double startPos = count / 4 * (defSizeZ + defDistance);
	dominos.push_back(new Domino(0, 0, startPos - (-1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
	for (int i = 1; i <= count / 4; i++)
	{
		dominos.push_back(new Domino(i*defSizeX / 2, 0, startPos-(i - 1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
		dominos.push_back(new Domino(-i*defSizeX / 2, 0, startPos-(i - 1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
	}
	for (int i = 1; i <= count / 4; i++)
	{
		dominos.push_back(new Domino(((count/4)-i)*defSizeX / 2, 0,  - (i - 1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
		dominos.push_back(new Domino(((-count/4)+i)*defSizeX / 2, 0,  - (i - 1)*(defSizeZ + (defDistance)), defSizeX, defSizeY, defSizeZ, 0));
	}
	started = false;
	ready = true;
	calcAngles();
}

void DominoSet::resetDominos()
{
    if (dominos.size()!=0)
    {
        for (std::vector<Domino*>::iterator i = dominos.begin(); i != dominos.end(); i++)
        {
            if ((*i)!=NULL)
            {
                (*i)->reset();
            }
        }
        ready = true;
    }
    else
    {
        ready = false;
    }    
    actualDomino = 0;
}

void DominoSet::start()
{
    resetDominos();
    unpause();
    if (ready)
    {
        ready = false;
        started = true;
    }
}

void DominoSet::nextStep()
{
    if (!started || paused)
    {
        return;
    }
    for (int i = 0; i <= actualDomino && i < dominos.size() ; i++)
    {
        Domino* act = dominos.at(i);
        double nextAngle = act->getTilt() + defStepAngle;
        
        if (i==actualDomino && nextAngle >= contactAngle ) //jezeli pochylil sie na tyle zeby uderzyc
        {
            actualDomino++;
        }
        if (nextAngle <= restingAngle) //jezeli pochylil sie na tyle zeby siê oprzec
        {
            act->step(defStepAngle+i*(0.4));
        }
        else if (i == dominos.size()-1)
        {
            act->step(defStepAngle);
        }
        else
        {
            act->setTilt(restingAngle);
        }
    }
    if (actualDomino == dominos.size() && dominos.at(actualDomino - 1)->isResting())
    {   
        started = false;
        ready = false;
        actualDomino = 0;
    }
}

void DominoSet::clear()
{
    if (dominos.size() != 0)
    {
        for (std::vector<Domino*>::iterator i = dominos.begin(); i != dominos.end(); i++)
        {
            delete (*i);
        }
        dominos.clear();
    }
    ready = false;
    started = false;
    actualDomino = 0;
}

void DominoSet::draw()
{
    if (dominos.size()!=0)
    {
        for (std::vector<Domino*>::iterator i = dominos.begin(); i != dominos.end(); i++)
        {
            if ((*i) != NULL)
            {
                (*i)->draw();
            }
        }
    }
}

void DominoSet::pause()
{
    if (paused)
    {
        unpause();
    }
    else
    {
        paused = true;
    }
}

void DominoSet::unpause()
{
    paused = false;
}

void DominoSet::calcAngles()
{
    double contactAngleRad = std::acos((double)defDistance / defSizeY);
    double restingAngleRad = std::atan((double)defSizeZ / (defDistance + defSizeZ));
    contactAngle = 90 - (contactAngleRad * 180 / M_PI);
    restingAngle = 90 - (restingAngleRad * 180 / M_PI);
}