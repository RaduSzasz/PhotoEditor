#include "brightnesswindow.h"
#include "ui_brightnesswindow.h"

BrightnessWindow::BrightnessWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::BrightnessWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    filter = new BrightnessFilter;
    bfilter = static_cast<BrightnessFilter*>(filter);
}

BrightnessWindow::~BrightnessWindow()
{
    delete ui;
}

void BrightnessWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void BrightnessWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    ui->lineEdit->setText(QString::number(value));
    bfilter->setValue(value);
    apply();
}

void BrightnessWindow::on_okButton_clicked()
{
    emit onOk();
}

void BrightnessWindow::on_cancelButton_clicked()
{
    emit onCancel();
}

void BrightnessWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    if(value > 150) value = 150;
    if(value < -150) value = -150;
    ui->horizontalSlider->setValue(value);
    bfilter->setValue(value);
    apply();
}
