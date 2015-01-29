#include "threadedfilterapplier.h"

ThreadedFilterApplier::ThreadedFilterApplier(QObject *parent) :
    QThread(parent)
{
    this->result = 0;
}

Filter* ThreadedFilterApplier::getFilter() const
{
    return this->filter;
}

void ThreadedFilterApplier::setFilter(Filter *value)
{
    this->filter = value;
    connect(this->filter, SIGNAL(onProgress(int)), this, SLOT(filterProgress(int)));
    connect(this->filter, SIGNAL(onFinish()), this, SLOT(filterFinish()));
}

void ThreadedFilterApplier::run()
{
    ProgressBarWindow *w = new ProgressBarWindow;
    w->setMaxValue(this->filter->getPicture()->getWidth());
    w->setModal(true);
    w->show();
    connect(this, SIGNAL(onProgress(int)), w, SLOT(update(int)));
    if (this->filter != null) {
        this->result = filter->apply();
        emit onFinish();
    }
    w->close();
    delete(w);
}

Picture* ThreadedFilterApplier::getResult() const
{
    return this->result;
}

void ThreadedFilterApplier::filterProgress(int current)
{
    emit onProgress(current);
}

void ThreadedFilterApplier::filterFinish()
{
    emit onFinish();
}
