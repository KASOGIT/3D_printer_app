#include "pointstl.h"

pointstl::pointstl()
{
}

pointstl::pointstl(float xCoord, float yCoord, float zCoord)
{
    setCoords(xCoord, yCoord, zCoord);
}

pointstl::pointstl(const pointstl &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

pointstl    &pointstl::operator =(const pointstl &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return (*this);
}

bool    operator ==(const pointstl    &p1, const pointstl &p2)
{
    if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
        return (true);

    return (false);
}

float   pointstl::getCoord(short numCoord) const
{
    if (numCoord == 1)
        return (x);
    else if (numCoord == 2)
        return (y);
    else if (numCoord == 3)
        return (z);

    return (0.);
}

void    pointstl::setCoord(short numCoord, float value)
{
    if (numCoord == 1)
        x = value;
    else if (numCoord == 2)
        y = value;
    else if (numCoord == 3)
        z = value;
}

void    pointstl::setCoords(float xCoord, float yCoord, float zCoord)
{
    x = xCoord;
    y = yCoord;
    z = zCoord;
}

void    pointstl::rotateOnAxis(short numCoord, float angle)
{
    if (numCoord == 1)
        rotateOnX(angle);
    else if (numCoord == 2)
        rotateOnY(angle);
    else if (numCoord == 3)
        rotateOnZ(angle);
}

void    pointstl::rotateOnX(float angle)
{
    float save_y(y);

    y = y * qCos(angle * 180 / 3.141592653) + z * -qSin(angle * 180 / 3.141592653);
    z = save_y * qSin(angle * 180 / 3.141592653) + z * qCos(angle * 180 / 3.141592653);
}

void    pointstl::rotateOnY(float angle)
{
    float save_x(x);

    x = x * qCos(angle * 180 / 3.141592653) + z * qSin(angle * 180 / 3.141592653);
    z = save_x * -qSin(angle * 180 / 3.141592653) + z * qCos(angle * 180 / 3.141592653);
}

void    pointstl::rotateOnZ(float angle)
{
    float save_x(x);

    x = x * qCos(angle * 180 / 3.141592653) + y * -qSin(angle * 180 / 3.141592653);
    y = save_x * qSin(angle * 180 / 3.141592653) + y * qCos(angle * 180 / 3.141592653);
}

void    pointstl::resizeCoords(float resize)
{
    x *= resize;
    y *= resize;
    z *= resize;
}
