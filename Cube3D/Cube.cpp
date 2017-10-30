#include "stdafx.h"
#include "Cube.h"

Color::Color()
{
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Cube::Cube(float _size, bool _solid)
{
    size = _size;
    solid = _solid;
}

void Cube::setColor(int face, Color c)
{
    if (face >= 0 && face < 6)
    {
        color[face].r = c.r;
        color[face].g = c.g;
        color[face].b = c.b;
    }
}

void Cube::setColor(Color c)
{
    for (int i = 0; i < 6; i++)
    {
        setColor(i, c);
    }
}

void Cube::display()
{
    GLenum mode = solid ? GL_FILL : GL_LINE;
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    glBegin(GL_QUADS);

    //Front
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);

    //Back
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);

    //Up
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);

    //Down
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);

    //Left
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);

    //Right
    glVertex3f(size, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);

    glEnd();
}