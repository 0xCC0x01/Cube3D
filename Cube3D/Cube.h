#ifndef _CUBE_H_
#define _CUBE_H_


class Color
{
public:
    float r;
    float g;
    float b;

public:
    Color();
};


class Cube
{
private:
    /* solid or wire cube */
    bool solid;
    /* side length */
    float size;
    /* colors of 6 faces */
    Color color[6];

public:
    float dir;
    float rotX;
    float rotY;
    float rotZ;

    Cube(float _size, bool _solid = true);

    /* set color for one single face */
    void setColor(int face, Color c);

    /* set the same color for all 6 faces */
    void setColor(Color c);

    /* display the cube */
    void display();
};


#endif /* _CUBE_H_ */