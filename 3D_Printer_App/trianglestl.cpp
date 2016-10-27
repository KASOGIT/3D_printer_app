#include "trianglestl.h"

triangleStl::triangleStl()
{
}

triangleStl::triangleStl(const triangleStl &other)
{
    vertex1 = other.vertex1;
    vertex2 = other.vertex2;
    vertex3 = other.vertex3;
}

triangleStl &triangleStl::operator =(const triangleStl &other)
{
    vertex1 = other.vertex1;
    vertex2 = other.vertex2;
    vertex3 = other.vertex3;

    return (*this);
}

void    triangleStl::setVertex(short numVertex, pointstl vertex)
{
    if (numVertex == 1)
        vertex1 = vertex;
    else if (numVertex == 2)
        vertex2 = vertex;
    else if (numVertex == 3)
        vertex3 = vertex;
}

bool    triangleStl::sameSide(const pointstl &p1, const pointstl &p2, const pointstl &a, const pointstl &b) const
{
    pointstl cp1, cp2;
    pointstl v1, v2, v3;

    // vector AB.
    v1.x = b.x - a.x;
    v1.y = b.y - a.y;
    v1.z = b.z - a.z;

    // vector AP
    v2.x = p1.x - a.x;
    v2.y = p1.y - a.y;
    v2.z = p1.z - a.z;

    // vector AP2
    v3.x = p2.x - a.x;
    v3.y = p2.y - a.y;
    v3.z = p2.z - a.z;

    // cross product v1 * v2 (AB & AP)
    cp1.x = v1.y * v2.z - v1.z * v2.y;
    cp1.y = v1.z * v2.x - v1.x * v2.z;
    cp1.z = v1.x * v2.y - v1.y * v2.x;

    // cross product v1 * v3 (AB & AP2)
    cp2.x = v1.y * v3.z - v1.z * v3.y;
    cp2.y = v1.z * v3.x - v1.x * v3.z;
    cp2.z = v1.x * v3.y - v1.y * v3.x;

    // dot product cp1 * cp2
    if ((cp1.x * cp2.x + cp1.y * cp2.y + cp1.z * cp2.z) >= 0)
      return (true);
    return (false);
}

bool    triangleStl::isInTriangle(float xCoord, float yCoord, float zCoord) const
{
    pointstl    point(xCoord, yCoord, zCoord);

    // if point is on the side of AB as C and also of BC as A and of CA as B then it is inside the triangle.
    if (sameSide(point, vertex1, vertex2, vertex3) && sameSide(point, vertex2, vertex1, vertex3) && sameSide(point, vertex3, vertex1, vertex2))
        return (true);
    return (false);
}

float   triangleStl::getMinY() const
{
    if (vertex1.y <= vertex2.y && vertex1.y <= vertex3.y)
        return (vertex1.y);
    else if (vertex2.y <= vertex1.y && vertex2.y <= vertex3.y)
        return (vertex2.y);
    else
        return (vertex3.y);
}

float   triangleStl::getMaxY() const
{
    if (vertex1.y >= vertex2.y && vertex1.y >= vertex3.y)
        return (vertex1.y);
    else if (vertex2.y >= vertex1.y && vertex2.y >= vertex3.y)
        return (vertex2.y);
    else
        return (vertex3.y);
}

float   triangleStl::getMinZ() const
{
    if (vertex1.z <= vertex2.z && vertex1.z <= vertex3.z)
        return (vertex1.z);
    else if (vertex2.z <= vertex1.z && vertex2.z <= vertex3.z)
        return (vertex2.z);
    else
        return (vertex3.z);
}

float   triangleStl::getMaxZ() const
{
    if (vertex1.z >= vertex2.z && vertex1.z >= vertex3.z)
        return (vertex1.z);
    else if (vertex2.z >= vertex1.z && vertex2.z >= vertex3.z)
        return (vertex2.z);
    else
        return (vertex3.z);
}

float   triangleStl::getMinX() const
{
    if (vertex1.x <= vertex2.x && vertex1.x <= vertex3.x)
        return (vertex1.x);
    else if (vertex2.x <= vertex1.x && vertex2.x <= vertex3.x)
        return (vertex2.x);
    else
        return (vertex3.x);
}

float   triangleStl::getMaxX() const
{
    if (vertex1.x >= vertex2.x && vertex1.x >= vertex3.x)
        return (vertex1.x);
    else if (vertex2.x >= vertex1.x && vertex2.x >= vertex3.x)
        return (vertex2.x);
    else
        return (vertex3.x);
}
