#include "resizefilter.h"

ResizeFilter::ResizeFilter(QObject *parent) :
    Filter(parent)
{
    _x = 0;
    _y = 0;
}

void ResizeFilter::setX(const int x)
{
    this->_x = x;
}

void ResizeFilter::setY(const int y)
{
    this->_y = y;
}

int ResizeFilter::getX() const
{
    return this->_x;
}

int ResizeFilter::getY() const
{
    return this->_y;
}

Picture* ResizeFilter::apply()
{
    Picture *result = new Picture(this->pic->getResizedVersion(this->_x, this->_y));
    return result;
}

