#include "myGLWidget_abstract.h"

MyGLWidget_abstract::MyGLWidget_abstract(QWidget *parent, int framesPerSecond)
    : QGLWidget(parent)
{
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde(1000);
        int timerInterval(seconde / framesPerSecond);

        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start(timerInterval);
    }
}

void    MyGLWidget_abstract::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
    }
}

void    MyGLWidget_abstract::resizeGL(int w, int h)
{
    if(h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(70.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void    MyGLWidget_abstract::timeOutSlot()
{
    updateGL();
}

void    MyGLWidget_abstract::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi(3.1415926535897932384626433832795);
    GLdouble fW, fH;

    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void MyGLWidget_abstract::normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 0)
        angle -= 360 * 16;
}
