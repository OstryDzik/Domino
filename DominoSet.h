#pragma once
#include "Domino.h"
#include <vector>

class DominoSet : public Drawable
{
private:
    int defSizeX;
    int defSizeY;
    int defSizeZ;
    int defDistance;
    std::vector<Domino*>dominos;
    double defStepAngle;
    double restingAngle;
    double contactAngle;
    bool started;
    bool ready;
    bool paused;
    int actualDomino;
public:
    DominoSet(int count);
    ~DominoSet();
    void draw();
    void resetDominos();
    void start();
    void loadDefaultSet(int count);
    void loadYSet(int count);
	void loadDiamondSet(int count);
    void nextStep();
    void clear();
    void pause();
    void unpause();
    void calcAngles();
};

