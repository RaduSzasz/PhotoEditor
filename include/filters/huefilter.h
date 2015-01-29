#ifndef HUEFILTER_H
#define HUEFILTER_H

#include "filter.h"

class HueFilter : public Filter
{
private:
    int _value;
public:
    explicit HueFilter(QObject *parent = 0);
    void setValue(const int value);
    int getValue() const;
    virtual Picture* apply();
};

#endif // HUEFILTER_H
