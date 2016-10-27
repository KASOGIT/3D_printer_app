#include "line.h"

line::line()
{
    m_area = 0;
    m_defined = false;
}

line::line(const line &other)
{
    m_lineDef.first = other.m_lineDef.first;
    m_lineDef.second = other.m_lineDef.second;
    m_area = other.m_area;
    m_defined = other.m_defined;
}

line    &line::operator =(const line &other)
{
    m_lineDef.first = other.m_lineDef.first;
    m_lineDef.second = other.m_lineDef.second;
    m_area = other.m_area;
    m_defined = other.m_defined;

    return (*this);
}

void    line::pushPoint(float xCoord, float yCoord, float zCoord, unsigned int area)
{
    if (!m_defined)
    {
        m_defined = true;
        m_area = area;
        m_lineDef.first.setCoords(xCoord, yCoord, zCoord);
        m_lineDef.second.setCoords(xCoord, yCoord, zCoord);
    }
    else
        m_lineDef.second.setCoords(xCoord, yCoord, zCoord);
}

bool    line::isDefined() const
{
    return (m_defined);
}

void    line::reset()
{
    m_defined = false;
}
