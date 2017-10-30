#include "stdafx.h"
#include "OpenGL.h"

#define ANGLE_DELTA      (0.5f)

COpenGL::COpenGL()
{
    angleX = 0.0f;
    angleY = 0.0f;
    angleZ = 0.0f;
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

void COpenGL::init(int width, int height)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glShadeModel(GL_FLAT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);;
}

bool COpenGL::setupPixelFormat(CDC *dc)  
{
    hDC = dc;

    static PIXELFORMATDESCRIPTOR pfd=  
    {  
        sizeof(PIXELFORMATDESCRIPTOR),  
        1,  
        PFD_DRAW_TO_WINDOW|  
        PFD_SUPPORT_OPENGL|  
        PFD_DOUBLEBUFFER,  
        PFD_TYPE_RGBA,  
        24,  
        0,0,0,0,0,0,  
        0,  
        0,  
        0,  
        0,0,0,0,  
        16,  
        0,  
        0,  
        PFD_MAIN_PLANE,  
        0,  
        0,0,0  
    };  
    int m_nPixelFormat=ChoosePixelFormat(hDC->GetSafeHdc(), &pfd);
    if (m_nPixelFormat==0)  
    {  
        return false;  
    }  
    if (SetPixelFormat(hDC->GetSafeHdc(), m_nPixelFormat, &pfd)==false)
    {  
        return false;  
    }  
    return true;  
}

void COpenGL::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -5);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    //glScalef(zoomSize, zoomSize, zoomSize);

    //glTranslatef(-1.0, -1.0, -1.0);
    rubik.display();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (1)//(rotate)
    {
        angleX += ANGLE_DELTA;
        angleY += ANGLE_DELTA;
        angleZ += ANGLE_DELTA;
    }

	SwapBuffers(hDC->GetSafeHdc());
}