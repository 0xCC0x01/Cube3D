#ifndef _RUBIKS_CUBE_H_
#define _RUBIKS_CUBE_H_

#include "Cube.h"

/* layers of the Rubik's cube: N*N*N */
#define LAYERS    (3)

typedef enum
{
    FRONT,
    BACK,
    UP,
    DOWN,
    LEFT,
    RIGHT
}CUBE_FACE;

class RubiksCube
{
private:
    float rotAngle;
    Cube *cube[LAYERS][LAYERS][LAYERS];

public:
    RubiksCube();
    ~RubiksCube();

    void init();

    void display();
    bool rotate(int face, bool clockwise);
};

#endif /* _RUBIKS_CUBE_H_ */