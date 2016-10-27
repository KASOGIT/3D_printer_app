#include "slicer.h"
#include"mainwindow.h"

slicer::slicer()
{
}

void    slicer::createSlices(const QList<triangleStl> &objectTriangles)
{
    cutTrianglesIntoLinesPerLayer(objectTriangles);
}

void    slicer::cutTrianglesIntoLinesPerLayer(const QList<triangleStl> &objectTriangles)
{
    int sampling(100); // mm.
    unsigned int area;
    layer   tmpLayer;
    line    tmpLine;
    QList<line> tmpListLines;
    QPair<float, float>   YInfo, ZInfo, XInfo;

    emit statusBarShow();
    YInfo = getYMinMax(objectTriangles);
    ZInfo = getZMinMax(objectTriangles);
    XInfo = getXMinMax(objectTriangles);
    for (int y = YInfo.first * sampling; y < YInfo.second * sampling; ++y)
    {
        for (int z = ZInfo.first * sampling; z < ZInfo.second * sampling; ++z)
        {
            area = 1;
            for (int x = XInfo.first * sampling; x < XInfo.second * sampling; ++x)
            {
                if (intersectTri(objectTriangles, (float)x / sampling, (float)y / sampling, (float)z / sampling))
                    tmpLine.pushPoint((float)x / sampling, (float)y / sampling, (float)z / sampling, area);
                else
                {
                    if (tmpLine.isDefined())
                    {
                        tmpListLines.append(tmpLine);
                        tmpLine.reset();
                        area++;
                    }
                }
            }
            if (!tmpListLines.isEmpty())
            {
                tmpLayer.linesLayer.append(tmpListLines);
                tmpListLines.clear();
            }
        }
        if (!tmpLayer.linesLayer.isEmpty())
        {
            objectLayers.append(tmpLayer);
            tmpLayer.linesLayer.clear();
        }
        emit valueChanged(y / (YInfo.second * sampling) * 100);
    }
    emit statusBarHide();
}

bool    slicer::intersectTri(const QList<triangleStl> &objectTriangles, float coordX, float coordY, float coordZ) const
{
    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (objectTriangles.at(i).isInTriangle(coordX, coordY, coordZ))
            return (true);
    }
    return (false);
}

QPair<float, float> slicer::getYMinMax(const QList<triangleStl> &objectTriangles)
{
    float   tmpMin, tmpMax;
    QPair<float, float> yInfo;

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.first = objectTriangles.at(i).getMinY();
        else
        {
            if (yInfo.first > (tmpMin = objectTriangles.at(i).getMinY()))
                yInfo.first = tmpMin;
        }
    }

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.second = objectTriangles.at(i).getMaxY();
        else
        {
            if (yInfo.second < (tmpMax = objectTriangles.at(i).getMaxY()))
                yInfo.second = tmpMax;
        }
    }

    return (yInfo);
}

QPair<float, float> slicer::getZMinMax(const QList<triangleStl> &objectTriangles)
{
    float   tmpMin, tmpMax;
    QPair<float, float> yInfo;

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.first = objectTriangles.at(i).getMinZ();
        else
        {
            if (yInfo.first > (tmpMin = objectTriangles.at(i).getMinZ()))
                yInfo.first = tmpMin;
        }
    }

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.second = objectTriangles.at(i).getMaxZ();
        else
        {
            if (yInfo.second < (tmpMax = objectTriangles.at(i).getMaxZ()))
                yInfo.second = tmpMax;
        }
    }

    return (yInfo);
}

QPair<float, float> slicer::getXMinMax(const QList<triangleStl> &objectTriangles)
{
    float   tmpMin, tmpMax;
    QPair<float, float> yInfo;

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.first = objectTriangles.at(i).getMinX();
        else
        {
            if (yInfo.first > (tmpMin = objectTriangles.at(i).getMinX()))
                yInfo.first = tmpMin;
        }
    }

    for (int i = 0; i < objectTriangles.size(); ++i)
    {
        if (i == 0)
            yInfo.second = objectTriangles.at(i).getMaxX();
        else
        {
            if (yInfo.second < (tmpMax = objectTriangles.at(i).getMaxX()))
                yInfo.second = tmpMax;
        }
    }

    return (yInfo);
}
