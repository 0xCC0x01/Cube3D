#include "stdafx.h"
#include "OpenGL.h"

#define ZOOM_DELTA        (0.15f)
#define ROTATE_DELTA      (0.5f)
#define SHUFFLE_STEPS     (5)

COpenGL::COpenGL()
{
    angleX = 0.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
    zoomSize = 1.0f;
}

COpenGL::~COpenGL()
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);

    if (hDC)
    {
        delete hDC;
    }
    hDC = NULL;
}

void COpenGL::setRot(int deltaX, int deltaY)
{
    angleY += (deltaX > 0 ? ROTATE_DELTA : -ROTATE_DELTA);
    angleX += (deltaY > 0 ? ROTATE_DELTA : -ROTATE_DELTA);
}

void COpenGL::init(int width, int height)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

bool COpenGL::setupPixelFormat(CDC *dc)  
{
    hDC = dc;

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL| PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(hDC->GetSafeHdc(), &pfd);
    if (pixelFormat == 0)
    {
        return false;
    }
    if (!SetPixelFormat(hDC->GetSafeHdc(), pixelFormat, &pfd))
    {
        return false;
    }

    return true;
}

void COpenGL::render(bool rotate)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -5);

    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    glScalef(zoomSize, zoomSize, zoomSize);

    if (!actions.empty())
    {
        ACTION currAct = actions[0];
        if (rubik.rotate(currAct.face, currAct.dir))
        {
            actions.erase(actions.begin());
        }
    }
    
    rubik.display();
    SwapBuffers(hDC->GetSafeHdc());

    if (rotate)
    {
        angleX += ROTATE_DELTA;
        angleY += ROTATE_DELTA;
        angleZ += ROTATE_DELTA;
    }
}

void COpenGL::zoomScene(short delta)
{
    if (delta > 0)
    {
        zoomSize += ZOOM_DELTA;
    }
    else if (zoomSize > ZOOM_DELTA)
    {
        zoomSize -= ZOOM_DELTA;
    }
}

void COpenGL::resetScene()
{
    angleX = 20.0f;
    angleY = 60.0f;
    angleZ = 0.0f;

    rubik.init();
    render(false);
}

void COpenGL::shuffleScene()
{
    srand((unsigned) time(NULL));
    for (int i = 0; i < SHUFFLE_STEPS; i++)
    {
        ACTION act;
        act.face = rand() % 6;
        act.dir = (rand() % 2) ? true : false;

        actions.push_back(act);
    }
}