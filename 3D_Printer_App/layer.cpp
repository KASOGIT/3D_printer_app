#include "layer.h"

layer::layer()
{
}

layer::layer(const layer &other)
{
    linesLayer = other.linesLayer;
}

layer   &layer::operator =(const layer &other)
{
    if (!linesLayer.isEmpty())
        linesLayer.clear();
    linesLayer = other.linesLayer;

    return (*this);
}
