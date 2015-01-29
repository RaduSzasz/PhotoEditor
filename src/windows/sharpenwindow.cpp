#include "sharpenwindow.h"
#include "ui_sharpenwindow.h"


SharpenWindow::SharpenWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::SharpenWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    filter = new SharpenFilter;
    sfilter = static_cast<SharpenFilter*>(filter);
}

SharpenWindow::~SharpenWindow()
{
    delete ui;
}

void SharpenWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void SharpenWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    ui->lineEdit->setText(QString::number(value));
    sfilter->setValue(value);
    apply();
}



void SharpenWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    ui->horizontalSlider->setValue(value);
    sfilter->setValue(value);
    apply();
}

void SharpenWindow::on_okButton_clicked()
{
    emit onOk();
}

void SharpenWindow::on_cancelButton_clicked()
{
    emit onCancel();
}
