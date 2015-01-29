#include "saturationwindow.h"
#include "ui_saturationwindow.h"

SaturationWindow::SaturationWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::SaturationWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    filter = new SaturationFilter;
    sfilter = static_cast<SaturationFilter*>(filter);
}

SaturationWindow::~SaturationWindow()
{
    delete ui;
}

void SaturationWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void SaturationWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    sfilter->setValue(value);
    ui->lineEdit->setText(QString::number(value));
    apply();
}

void SaturationWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    if(value > 100) value = 100;
    if(value < -100) value = 100;
    sfilter->setValue(value);
    ui->horizontalSlider->setValue(value);
    apply();
}

void SaturationWindow::on_okButton_clicked()
{
    emit onOk();
}

void SaturationWindow::on_cancelButton_clicked()
{
    emit onCancel();
}
