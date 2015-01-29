#ifndef BOXBLURFILTER_H
#define BOXBLURFILTER_H

#include <picture.h>
#include <filter.h>

class BoxBlurFilter : public Filter
{
private:
    int _radius;
public:
    explicit BoxBlurFilter(QObject *parent = 0);
    void setRadius(const int radius);
    int getRadius() const;
    virtual Picture* apply();
};

#endif // BOXBLURFILTER_H
