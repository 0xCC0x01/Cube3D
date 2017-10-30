#ifndef _OPENGL_H_
#define _OPENGL_H_

#include "RubiksCube.h"

class COpenGL
{
private:
    CDC *hDC;
    HGLRC hRC;
    RubiksCube rubik;

    float angleX;
    float angleY;
    float angleZ;

public:
    COpenGL();
    ~COpenGL();

    void init(int width, int height);
    bool setupPixelFormat(CDC *dc);
    void renderScene();
};

#endif /* _OPENGL_H_ */