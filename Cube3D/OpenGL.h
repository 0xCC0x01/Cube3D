#ifndef _OPENGL_H_
#define _OPENGL_H_

#include "RubiksCube.h"


typedef struct
{
    bool undo;
    bool dir;
    int face;
}ACTION;

class COpenGL
{
private:
    CDC *hDC;
    HGLRC hRC;
    /* Rubik's cube */
    RubiksCube rubik;
    /* rotate angle of the whole cube */
    float angleX;
    float angleY;
    float angleZ;
    /* zoom size of the cube */
    float zoomSize;

public:
    COpenGL();
    ~COpenGL();

    void init(int width, int height);
    bool setupPixelFormat(CDC *dc);

    void setRot(int deltaX, int deltaY);

    bool render(bool rotate = true, bool solid = true, ACTION *act = NULL);
    void resetScene();
    void zoomScene(short delta);
};

#endif /* _OPENGL_H_ */