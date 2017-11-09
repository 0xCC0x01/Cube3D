#ifndef _OPENGL_H_
#define _OPENGL_H_

#include "RubiksCube.h"
#include <vector>
using std::vector;


typedef struct
{
    int face;
    bool dir;
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
    /* rotate actions */
    vector <ACTION> actions;

public:
    COpenGL();
    ~COpenGL();

    void init(int width, int height);
    bool setupPixelFormat(CDC *dc);

    void setRot(int deltaX, int deltaY);
    void setAction(int face, bool clockwise);

    void render(bool rotate = true);
    void resetScene();
    void zoomScene(short delta);
    void shuffleScene();
};

#endif /* _OPENGL_H_ */