#include "huewindow.h"
#include "ui_huewindow.h"

HueWindow::HueWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::HueWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    filter = new HueFilter;
    hfilter = static_cast<HueFilter*>(filter);
}

HueWindow::~HueWindow()
{
    delete ui;
}

void HueWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void HueWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    ui->lineEdit->setText(QString::number(value));
    hfilter->setValue(value);
    apply();
}



void HueWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    while(value < 0)
        value += 360;
    while(value > 360)
        value -= 360;
    ui->horizontalSlider->setValue(value);
    hfilter->setValue(value);
    apply();
}
void HueWindow::on_okButton_clicked()
{
    emit onOk();
}

void HueWindow::on_cancelButton_clicked()
{
    emit onCancel();
}
