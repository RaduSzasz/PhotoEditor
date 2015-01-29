#include "filter.h"

Filter::Filter(QObject *parent)
{
    this->pic=0;
}

Filter::Filter(Picture* picture)
{
    this->pic = picture;
}

Picture* Filter::getPicture() const
{
    return this->pic;
}

void Filter::setPicture(Picture *value)
{
    this->pic = value;
}
