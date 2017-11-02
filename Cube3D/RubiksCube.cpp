#include "stdafx.h"
#include "RubiksCube.h"

Color green = Color(0.0f, 1.0f, 0.0f);
Color blue = Color(0.0f, 0.0f, 1.0f);
Color white = Color(1.0f, 1.0f, 1.0f);
Color yellow = Color(1.0f, 1.0f, 0.0f);
Color red = Color(1.0f, 0.0f, 0.0f);
Color orange = Color(0.93f, 0.49f, 0.19f);

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
                    cube[i][j][k]->setColor(FRONT, green);
                }
                if (k == 0)
                {
                    cube[i][j][k]->setColor(BACK, blue);
                }
                if (j == LAYERS - 1)
                {
                    cube[i][j][k]->setColor(UP, white);
                }
                if (j == 0)
                {
                    cube[i][j][k]->setColor(DOWN, yellow);
                }
                if (i == 0)
                {
                    cube[i][j][k]->setColor(LEFT, red);
                }
                if (i == LAYERS - 1)
                {
                    cube[i][j][k]->setColor(RIGHT, orange);
                }
            }
        }
    }
}

void RubiksCube::display()
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

                cube[i][j][k]->display();
                
                glTranslatef(-x, -y, -z);
                cube[i][j][k]->rotate(false);
            }
        }
    }
}

bool RubiksCube::rotate(int face, bool clockwise)
{
    bool done = false;

    if (rotAngle <= 0.0f)
    {
        init();
    }
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
    }

    return done;
}