#ifndef _RUBIKS_CUBE_H_
#define _RUBIKS_CUBE_H_

#include "Cube.h"

/* layers of the Rubik's cube: N*N*N */
#define LAYERS    (3)

class RubiksCube
{
private:
    Cube *cube[LAYERS][LAYERS][LAYERS];

public:
    RubiksCube();
    ~RubiksCube();

    void display();
    void rotateU(bool clockwise);
};

#endif /* _RUBIKS_CUBE_H_ */