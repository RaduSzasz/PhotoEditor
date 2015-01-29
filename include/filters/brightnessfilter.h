#ifndef BRIGHTNESSFILTER_H
#define BRIGHTNESSFILTER_H

#include <filter.h>

class BrightnessFilter : public Filter
{
private:
    int _value;
public:
    explicit BrightnessFilter(QObject *parent = 0);
    void setValue(const int val);
    int getValue() const;
    virtual Picture* apply();
};

#endif // BRIGHTNESSFILTER_H
