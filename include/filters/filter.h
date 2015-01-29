#ifndef FILTER_H
#define FILTER_H
#include "picture.h"
#include "color.h"

class Filter : public QObject
{
    Q_OBJECT
protected:
    Picture* pic;
public:
    explicit Filter(QObject *parent = 0);
    Filter(Picture* picture);

    Picture* getPicture() const;
    void setPicture(Picture* value);

    virtual Picture* apply() = 0;

signals:
    void onProgress(int current);
    void onFinish();
};

#endif // FILTER_H
