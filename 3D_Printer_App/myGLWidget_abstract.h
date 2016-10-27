#ifndef MYGLWIDGET_ABSTRACT_H
#define MYGLWIDGET_ABSTRACT_H

// OpenGL includes - Included here and hence shared by all the files that need OpenGL headers.
#if QT_VERSION >= 0x040000
#include <QGLWidget>
#else
# include <qgl.h>
#endif

// GLU was removed from Qt in version 4.8
#ifdef Q_OS_MAC
#include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif
#include<QtOpenGL>

class MyGLWidget_abstract : public QGLWidget
{
    Q_OBJECT

public:
    explicit    MyGLWidget_abstract(QWidget *parent = 0, int framesPerSecond = 0);
    void    normalizeAngle(int &angle);

protected:
    virtual void    initializeGL() = 0;
    void    keyPressEvent(QKeyEvent *);
    virtual void    paintGL() = 0;
    void    resizeGL(int w, int h);
    void    perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

public slots:
    void    timeOutSlot();

private:
    QTimer  *t_Timer;
};

#endif // MYGLWIDGET_ABSTRACT_H
