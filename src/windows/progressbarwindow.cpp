#include "progressbarwindow.h"
#include "ui_progressbarwindow.h"

ProgressBarWindow::ProgressBarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBarWindow)
{
    ui->setupUi(this);
}

ProgressBarWindow::~ProgressBarWindow()
{
    delete ui;
}

void ProgressBarWindow::setMaxValue(int value)
{
    ui->progressBar->setMaximum(value);
}

void ProgressBarWindow::update(int progress)
{
    ui->progressBar->setValue(progress);
}
