#ifndef POINTSTL_H
#define POINTSTL_H

#include<QtCore/qmath.h>
#include<QList>

class pointstl
{
public:
    pointstl();
    pointstl(float xCoord, float yCoord, float zCoord);
    pointstl(const pointstl &other);
    pointstl    &operator =(const pointstl   &other);
    //bool    operator ==(const pointstl &p1, const pointstl  &p2);

    float   x;
    float   y;
    float   z;

    void    setCoord(short numCoord, float value);
    void    setCoords(float xCoord, float yCoord, float zCoord);
    float   getCoord(short numCoord) const;

    void    rotateOnAxis(short numCoord, float angle);
    void    rotateOnX(float angle);
    void    rotateOnY(float angle);
    void    rotateOnZ(float angle);

    void    resizeCoords(float resize);
};

#endif // POINTSTL_H
