#ifndef BLACKWHITEFILTER_H
#define BLACKWHITEFILTER_H

#include <filter.h>
#include <picture.h>

class BlackWhiteFilter : public Filter
{
private:
    int R, G, B;
public:
    explicit BlackWhiteFilter(QObject *parent = 0);
    virtual Picture* apply();
    void setR(const int value);
    void setG(const int value);
    void setB(const int value);
    int getR() const;
    int getG() const;
    int getB() const;

};

#endif // BLACKWHITEFILTER_H
