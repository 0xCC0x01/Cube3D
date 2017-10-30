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

                glColor3f(1.0f*(i+1)/LAYERS, 1.0f*(j+1)/LAYERS, 1.0f*(k+1)/LAYERS);

                glTranslatef(x, y, z);
                cube[i][j][k]->display();
                glTranslatef(-x, -y, -z);
            }
        }
    }
}