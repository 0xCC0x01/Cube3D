#include "stdafx.h"
#include "Cube.h"

Cube::Cube(float _size, bool _solid)
{
    size = _size;
    solid = _solid;

    dir = 1.0f;

    rotX = 0.0f;
    rotY = 0.0f;
    rotZ = 0.0f;
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

void Cube::setDir(bool clockwise)
{
    dir = clockwise ? -1.0f : 1.0f;
}

void Cube::setRotX(float angle)
{
    rotX = angle;
}

void Cube::setRotY(float angle)
{
    rotY = angle;
}

void Cube::setRotZ(float angle)
{
    rotZ = angle;
}

void Cube::display(bool selfRotate)
{
    GLenum mode = solid ? GL_FILL : GL_LINE;
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    glBegin(GL_QUADS);

    /* Front */
    if (!selfRotate)
    {
        glColor3f(color[0].r, color[0].g, color[0].b);
    }
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);

    /* Back */
    if (!selfRotate)
    {
        glColor3f(color[1].r, color[1].g, color[1].b);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);

    /* Up */
    if (!selfRotate)
    {
        glColor3f(color[2].r, color[2].g, color[2].b);
    }
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);

    /* Down */
    if (!selfRotate)
    {
        glColor3f(color[3].r, color[3].g, color[3].b);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);

    /* Left */
    if (!selfRotate)
    {
        glColor3f(color[4].r, color[4].g, color[4].b);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);

    /* Right */
    if (!selfRotate)
    {
        glColor3f(color[5].r, color[5].g, color[5].b);
    }
    glVertex3f(size, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);

    glEnd();
}

void Cube::rotate(bool derotate)
{
    float d = derotate ? dir : -dir;
    
    glRotatef(rotX, d, 0, 0);
    glRotatef(rotY, 0, d, 0);
    glRotatef(rotZ, 0, 0, d);
}