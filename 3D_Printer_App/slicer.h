#ifndef SLICER_H
#define SLICER_H

#include<QFile>
#include<fstream>
#include<QTextStream>
#include<QPair>
#include<QMainWindow>

#include"trianglestl.h"
#include"layer.h"

class slicer : public QObject
{
    Q_OBJECT

public:
    slicer();

    void    createSlices(const QList<triangleStl>   &objectTriangles);

    QList<layer>    objectLayers;

signals:
    void    valueChanged(int newValue);
    void    statusBarShow();
    void    statusBarHide();

private:
    void    cutTrianglesIntoLinesPerLayer(const QList<triangleStl>   &objectTriangles);
    bool    intersectTri(const QList<triangleStl> &objectTriangles, float coordX, float coordY, float coordZ) const;
    QPair<float, float> getYMinMax(const QList<triangleStl> &objectTriangles);
    QPair<float, float> getZMinMax(const QList<triangleStl> &objectTriangles);
    QPair<float, float> getXMinMax(const QList<triangleStl> &objectTriangles);
};

#endif // SLICER_H
