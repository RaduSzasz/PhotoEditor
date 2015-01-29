#ifndef ADJUSTMENTWINDOW_H
#define ADJUSTMENTWINDOW_H

#include <QDialog>
#include "picture.h"
#include "filter.h"
#include "threadedfilterapplier.h"
#include "progressbarwindow.h"

class AdjustmentWindow : public QDialog
{
    Q_OBJECT
public:
    explicit AdjustmentWindow(QWidget *parent = 0);
    void setPicture(Picture *pic);
    Picture* getPicture() const;
signals:
    void onRefresh();
    void onOk();
    void onCancel();

protected:
    virtual void apply() = 0;
    Picture *_copy;
    Filter *filter;
    ThreadedFilterApplier *filterApplier;
public slots:
    void ready();
private:


};

#endif // ADJUSTMENTWINDOW_H
