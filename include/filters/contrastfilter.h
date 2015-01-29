#ifndef CONTRASTFILTER_H
#define CONTRASTFILTER_H

#include "filter.h"

class ContrastFilter : public Filter
{
private:
    int _value;
public:
    explicit ContrastFilter(QObject *parent = 0);
    int getValue() const;
    void setValue(const int val);
    virtual Picture* apply();
};

#endif // CONTRASTFILTER_H
