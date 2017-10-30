#include "stdafx.h"
#include "RubiksCube.h"

RubiksCube::RubiksCube()
{
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
                float dir = cube[i][j][k]->dir;

                glColor3f(1.0f*(i+1)/LAYERS, 1.0f*(j+1)/LAYERS, 1.0f*(k+1)/LAYERS);

                glRotatef(cube[i][j][k]->rotX, dir, 0, 0);
                glRotatef(cube[i][j][k]->rotY, 0, dir, 0);
                glRotatef(cube[i][j][k]->rotZ, 0, 0, dir);

                glTranslatef(x, y, z);

                cube[i][j][k]->display();
                
                glTranslatef(-x, -y, -z);

                glRotatef(cube[i][j][k]->rotZ, 0, 0, -dir);
                glRotatef(cube[i][j][k]->rotY, 0, -dir, 0);
                glRotatef(cube[i][j][k]->rotX, -dir, 0, 0);
            }
        }
    }
}

void RubiksCube::rotateU(bool clockwise)
{
    for (int i = 0; i < LAYERS; i++)
    {
        for (int j = 0; j < LAYERS; j++)
        {
            for (int k = 0; k < LAYERS; k++)
            {
                float delta = (cube[i][j][k]->rotY < 90.0f) ? 10.0f : 0.0f;
                
                if (j == 1)
                {
                    cube[i][j][k]->rotX = 0;
                    cube[i][j][k]->rotY += delta;
                    cube[i][j][k]->rotZ = 0;
                }
                else
                {
                    cube[i][j][k]->rotX = 0;
                    cube[i][j][k]->rotY = 0;
                    cube[i][j][k]->rotZ = 0;
                }

                cube[i][j][k]->dir = (clockwise ? -1 : 1);
            }
        }
    }
}