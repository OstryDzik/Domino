#include "Scene.h"
#include <time.h>

int main(int argc, char** argv)
{
    srand(time(NULL));
    Scena::start(argc, argv);
    Scena::close();
}

