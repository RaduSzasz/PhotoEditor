#ifndef THREADEDFILTERAPPLIER_H
#define THREADEDFILTERAPPLIER_H

#include <QThread>
#include "filter.h"
#include "progressbarwindow.h"

class ThreadedFilterApplier : public QThread
{
    Q_OBJECT
private:
    Filter* filter;
    Picture* result;
public:
    explicit ThreadedFilterApplier(QObject *parent = 0);
    void setFilter(Filter* value);
    Filter* getFilter() const;
    Picture* getResult() const;
    void run();
signals:
    void onProgress(int current);
    void onFinish();

public slots:
    void filterProgress(int current);
    void filterFinish();
};

#endif // THREADEDFILTERAPPLIER_H
