#ifndef SATURATIONFILTER_H
#define SATURATIONFILTER_H

#include "filter.h"

class SaturationFilter : public Filter
{
private:
    int _value;
public:
    explicit SaturationFilter(QObject *parent = 0);
    void setValue(const int value);
    int getValue() const;
    virtual Picture* apply();
};

#endif // SATURATIONFILTER_H
