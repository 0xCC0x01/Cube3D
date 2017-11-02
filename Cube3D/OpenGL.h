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
    RubiksCube rubik;

    float angleX;
    float angleY;
    float angleZ;
    float zoomSize;

    vector <ACTION> actions;

public:
    COpenGL();
    ~COpenGL();

    void init(int width, int height);
    bool setupPixelFormat(CDC *dc);

    void setRot(int deltaX, int deltaY);

    void render(bool rotate = true);
    void resetScene();
    void zoomScene(short delta);
    void shuffleScene();
};

#endif /* _OPENGL_H_ */