#ifndef TRIANGLESTL_H
#define TRIANGLESTL_H

#include<QList>
#include"pointstl.h"

class   triangleStl
{
public:
    triangleStl();
    triangleStl(const triangleStl &other);
    triangleStl &operator=(const triangleStl &other);

    pointstl    vertex1;
    pointstl    vertex2;
    pointstl    vertex3;

    void    setVertex(short numVertex, pointstl vertex);
    bool    isInTriangle(float xCoord, float yCoord, float zCoord) const;

    float   getMinY() const;
    float   getMaxY() const;
    float   getMinZ() const;
    float   getMaxZ() const;
    float   getMinX() const;
    float   getMaxX() const;

private:
    bool    sameSide(const pointstl &p1, const pointstl &p2, const pointstl &a, const pointstl &b) const;
};

#endif // TRIANGLESTL_H
