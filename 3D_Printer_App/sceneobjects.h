#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include"myGLWidget_abstract.h"
//#include"trianglestl.h"
#include"slicer.h"

class SceneObjects : public MyGLWidget_abstract
{
public:
    SceneObjects(QWidget *parent, int framePerSecond);
    ~SceneObjects();

    void    initializeGL();
    void    paintGL();
    void    mousePressEvent(QMouseEvent *event);
    void    mouseMoveEvent(QMouseEvent *event);

    int getXRotation() const;
    int getYRotation() const;
    int getZRotation() const;
    float   getZoom() const;
    QList<triangleStl>  getObjectTriangles() const;
    void    resetObjectTriangles();

    slicer  *m_objectSlices;

    void    setInPath(bool  state);
    void    setZoom(float value);
    void    setXRotation(int angle);
    void    setYRotation(int angle);
    void    setZRotation(int angle);
    void    setObjectTriangles(const QList<triangleStl> &objectTriangles);

private:
    void    draw();
    void    drawGrid(float unit) const;
    void    enableLights();

    QList<triangleStl>  m_objectTriangles;

    int xRot;
    int yRot;
    int zRot;

    float   zoom;

    Qt::MouseButton lastButton;
    QPoint  lastPos;
};

#endif // SCENEOBJECTS_H
