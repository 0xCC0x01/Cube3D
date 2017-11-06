#ifndef _CUBE_H_
#define _CUBE_H_

class Color
{
public:
    float r;
    float g;
    float b;

public:
    Color() { r = 0.5f; g = 0.5f; b = 0.5f; };
    Color(unsigned char _r, unsigned char _g, unsigned char _b) { r = _r/255.0f; g = _g/255.0f; b = _b/255.0f; };
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
    /* rotate direction */
    float dir;
    /* rotate angle */
    float rotX;
    float rotY;
    float rotZ;

public:
    Cube(float _size, bool _solid = true);

    /* set color for one single face */
    void setColor(int face, Color c);
    
    /* set rotate direction */
    void setDir(bool clockwise);
    
    /* set rotate angle */
    void setRotX(float angle);
    void setRotY(float angle);
    void setRotZ(float angle);

    /* display the cube */
    void display(bool selfRotate);

    /* rotate or derotate the cube */
    void rotate(bool derotate);
};

#endif /* _CUBE_H_ */