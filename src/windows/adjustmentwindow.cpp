#include "adjustmentwindow.h"
#include "picturemanager.h"

AdjustmentWindow::AdjustmentWindow(QWidget *parent) :
    QDialog(parent)
{
    this->_copy = 0;
}

void AdjustmentWindow::setPicture(Picture *pic)
{
    this->_copy = new Picture(*pic);
    filter->setPicture(_copy);
    filterApplier = new ThreadedFilterApplier;
    filterApplier->setFilter(filter);
}

void AdjustmentWindow::ready()
{
    this->_copy = filterApplier->getResult();
    emit onRefresh();
}

Picture* AdjustmentWindow::getPicture() const
{
    return _copy;
}
