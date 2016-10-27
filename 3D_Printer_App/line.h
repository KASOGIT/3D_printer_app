#ifndef LINE_H
#define LINE_H

#include<QPair>
#include"pointstl.h"

class line
{
public:
    line();
    line(const line &other);
    line    &operator =(const line &other);

    void    pushPoint(float xCoord, float yCoord, float zCoord, unsigned int area);
    bool    isDefined() const;
    void    reset();

    QPair<pointstl, pointstl>   m_lineDef;

    unsigned int m_area;

private:
    bool    m_defined;
};

#endif // LINE_H
