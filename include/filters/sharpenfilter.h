#ifndef SHARPENFILTER_H
#define SHARPENFILTER_H

#include <filter.h>

class SharpenFilter : public Filter
{
private:
    int _value;
public:
    explicit SharpenFilter(QObject *parent = 0);
    void setValue(const int &val);
    int getValue() const;
    virtual Picture* apply();
};

#endif // SHARPENFILTER_H
