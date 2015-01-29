#ifndef RESIZEFILTER_H
#define RESIZEFILTER_H

#include "filter.h"

class ResizeFilter : public Filter
{
private:
    int _x, _y;
public:
    explicit ResizeFilter(QObject *parent = 0);
    void setX(const int x);
    void setY(const int y);
    int getX() const;
    int getY() const;
    virtual Picture* apply();
};

#endif // RESIZEFILTER_H
