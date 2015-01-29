#include "resizewindow.h"
#include "ui_resizewindow.h"

ResizeWindow::ResizeWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::ResizeWindow)
{
    ui->setupUi(this);
    filter = new ResizeFilter;
    rfilter = static_cast<ResizeFilter*>(filter);
    ui->checkBox->setChecked(true);
}

ResizeWindow::~ResizeWindow()
{
    delete ui;
}

void ResizeWindow::on_widthEdit_textEdited(const QString &arg1)
{
    double raport = (double)rfilter->getPicture()->getWidth() / (double)rfilter->getPicture()->getHeight();
    int xVal = ui->widthEdit->text().toInt(), yVal;
    rfilter->setX(xVal);
    if(ui->checkBox->isChecked())
    {
        yVal = (double)xVal / raport;
        ui->heightEdit->setText(QString::number(yVal));
        rfilter->setY(yVal);
    }
}

void ResizeWindow::on_heightEdit_textEdited(const QString &arg1)
{
    double raport = (double)rfilter->getPicture()->getWidth() / (double)rfilter->getPicture()->getHeight();
    int yVal = ui->heightEdit->text().toInt(), xVal;
    rfilter->setY(yVal);
    if(ui->checkBox->isChecked())
    {
        xVal = raport * yVal;
        ui->widthEdit->setText(QString::number(xVal));
        rfilter->setX(xVal);
    }
}

void ResizeWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void ResizeWindow::display()
{
    ui->widthEdit->setText(QString::number(rfilter->getPicture()->getWidth()));
    ui->heightEdit->setText(QString::number(rfilter->getPicture()->getHeight()));
    rfilter->setX(rfilter->getPicture()->getWidth());
    rfilter->setY(rfilter->getPicture()->getHeight());
}

void ResizeWindow::on_okButton_clicked()
{
    apply();
    emit onOk();
}

void ResizeWindow::on_cancelButton_clicked()
{
    emit onCancel();
}
