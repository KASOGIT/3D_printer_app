#ifndef LAYER_H
#define LAYER_H

#include<QList>
#include"line.h"

class layer
{
public:
    layer();
    layer(const layer &other);
    layer   &operator =(const layer &other);

    QList<QList<line> > linesLayer;
};

#endif // LAYER_H
