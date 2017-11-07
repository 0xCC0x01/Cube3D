#include "stdafx.h"
#include "RubiksCube.h"

static Color green = Color(146, 208, 80);
static Color blue = Color(0, 176, 240);
static Color white = Color(255, 255, 255);
static Color yellow = Color(255, 255, 0);
static Color red = Color(255, 90, 90);
static Color orange = Color(250, 150, 50);

static Color colorTable[6] = {green, blue, white, yellow, red, orange};

int CubeColor[6][LAYERS][LAYERS] =
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
    {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
    {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
    {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
    {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}
};

int CubeColor2[6][LAYERS][LAYERS] =
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
    {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
    {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
    {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
    {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}
};

RubiksCube::RubiksCube()
{
    rotAngle = 0.0f;

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {
                cube[i][j][k] = new Cube(2.0f/LAYERS);
            }
        }
    }
}

RubiksCube::~RubiksCube()
{
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {
                delete cube[i][j][k];
            }
        }
    }
}

void RubiksCube::init()
{
    for (int f = 0; f < 6; f++)
    {
        for (int i = 0; i < LAYERS; i++)
        {
            for (int j = 0; j < LAYERS; j++)
            {
                CubeColor[f][i][j] = f;
                CubeColor2[f][i][j] = f;
            }
        }
    }

    setColor();
}

void RubiksCube::setColor()
{
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {
                cube[i][j][k]->setRotX(0.0f);
                cube[i][j][k]->setRotY(0.0f);
                cube[i][j][k]->setRotZ(0.0f);

                if (k == LAYERS - 1)
                {
                    cube[i][j][k]->setColor(FRONT, colorTable[CubeColor[FRONT][i][j]]);
                }
                if (k == 0)
                {
                    cube[i][j][k]->setColor(BACK, colorTable[CubeColor[BACK][i][j]]);
                }
                if (j == LAYERS - 1)
                {
                    cube[i][j][k]->setColor(UP, colorTable[CubeColor[UP][i][k]]);
                }
                if (j == 0)
                {
                    cube[i][j][k]->setColor(DOWN, colorTable[CubeColor[DOWN][i][k]]);
                }
                if (i == 0)
                {
                    cube[i][j][k]->setColor(LEFT, colorTable[CubeColor[LEFT][j][k]]);
                }
                if (i == LAYERS - 1)
                {
                    cube[i][j][k]->setColor(RIGHT, colorTable[CubeColor[RIGHT][j][k]]);
                }
            }
        }
    }
}

void RubiksCube::display(bool selfRotate)
{
    float size = 2.0f/LAYERS;
    
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {
                float x = -1.0f + i*size;
                float y = -1.0f + j*size;
                float z = -1.0f + k*size;

                glColor3f(1.0f*(i+1)/LAYERS, 1.0f*(j+1)/LAYERS, 1.0f*(k+1)/LAYERS);

                cube[i][j][k]->rotate(true);
                glTranslatef(x, y, z);

                cube[i][j][k]->display(selfRotate);
                
                glTranslatef(-x, -y, -z);
                cube[i][j][k]->rotate(false);
            }
        }
    }
}

bool RubiksCube::rotateFace(int face, bool clockwise)
{
    bool done = false;
    rotAngle += 2.0f;

    if (rotAngle > 90.0f)
    {
        rotAngle = 90.0f;
        done = true;
    }

    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {   
                if ((RIGHT == face && i == LAYERS - 1) || (LEFT == face && i == 0))
                {
                    cube[i][j][k]->setRotX(rotAngle);
                }
                else if ((UP == face && j == LAYERS - 1) || (DOWN == face && j == 0))
                {
                    cube[i][j][k]->setRotY(rotAngle);
                }
                else if ((FRONT == face && k == LAYERS - 1) || (BACK == face && k == 0))
                {
                    cube[i][j][k]->setRotZ(rotAngle);
                }

                cube[i][j][k]->setDir(clockwise);
            }
        }
    }

    if (done)
    {
        rotAngle = 0.0f;
        rotateColor(face, clockwise);
        setColor();
    }

    return done;
}

void RubiksCube::rotateColor(int face, bool clockwise)
{
    if (FRONT == face || BACK == face)
    {
        int n = (FRONT == face) ? LAYERS - 1 : 0;
        for (int i = 0; i < LAYERS; i++)
        {
            if (clockwise)
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][j][LAYERS - 1 - i] = CubeColor2[face][i][j];
                }
                CubeColor[RIGHT][LAYERS - 1 - i][n] = CubeColor2[UP][i][n];
                CubeColor[DOWN][i][n] = CubeColor2[RIGHT][i][n];
                CubeColor[LEFT][i][n] = CubeColor2[DOWN][LAYERS - 1 - i][n];
                CubeColor[UP][i][n] = CubeColor2[LEFT][i][n];
            }
            else
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][LAYERS - 1 - j][i] = CubeColor2[face][i][j];
                }
                CubeColor[UP][i][n] = CubeColor2[RIGHT][LAYERS - 1 - i][n];
                CubeColor[RIGHT][i][n] = CubeColor2[DOWN][i][n];
                CubeColor[DOWN][LAYERS - 1 - i][n] = CubeColor2[LEFT][i][n];
                CubeColor[LEFT][i][n] = CubeColor2[UP][i][n];
            }
        }
    }
    else if (UP == face || DOWN == face)
    {
        int n = (UP == face) ? LAYERS - 1 : 0;
        for (int i = 0; i < LAYERS; i++)
        {
            if (clockwise)
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][LAYERS - j - 1][i] = CubeColor2[face][i][j];
                }
                CubeColor[RIGHT][n][i] = CubeColor2[BACK][i][n];
                CubeColor[FRONT][i][n] = CubeColor2[RIGHT][n][LAYERS - 1 - i];
                CubeColor[LEFT][n][i] = CubeColor2[FRONT][i][n];
                CubeColor[BACK][i][n] = CubeColor2[LEFT][n][LAYERS - 1 - i];
            }
            else
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][j][LAYERS - 1 - i] = CubeColor2[face][i][j];
                }
                CubeColor[BACK][i][n] = CubeColor2[RIGHT][n][i];
                CubeColor[RIGHT][n][LAYERS - 1 - i] = CubeColor2[FRONT][i][n];
                CubeColor[FRONT][i][n] = CubeColor2[LEFT][n][i];
                CubeColor[LEFT][n][LAYERS - 1 - i] = CubeColor2[BACK][i][n];
            }
        }
    }
    else if (LEFT == face || RIGHT == face)
    {
        int n = (LEFT == face) ? 0 : LAYERS - 1;
        for (int i = 0; i < LAYERS; i++)
        {
            if (clockwise)
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][j][LAYERS - i - 1] = CubeColor2[face][i][j];
                }
                CubeColor[DOWN][n][i] = CubeColor2[BACK][n][LAYERS - 1 - i];
                CubeColor[FRONT][n][i] = CubeColor2[DOWN][n][i];
                CubeColor[UP][n][i] = CubeColor2[FRONT][n][LAYERS - 1 - i];
                CubeColor[BACK][n][i] = CubeColor2[UP][n][i];
            }
            else
            {
                for (int j = 0; j < LAYERS; j++)
                {
                    CubeColor[face][LAYERS - 1 - j][i] = CubeColor2[face][i][j];
                }
                CubeColor[BACK][n][LAYERS - 1 - i] = CubeColor2[DOWN][n][i];
                CubeColor[DOWN][n][i] = CubeColor2[FRONT][n][i];
                CubeColor[FRONT][n][LAYERS - 1 - i] = CubeColor2[UP][n][i];
                CubeColor[UP][n][i] = CubeColor2[BACK][n][i];
            }
        }
    }

    for (int f = 0; f < 6; f++)
    {
        for (int i = 0; i < LAYERS; i++)
        {
            for (int j = 0; j < LAYERS; j++)
            {
                CubeColor2[f][i][j] = CubeColor[f][i][j];
            }
        }
    }
}