#include "blackandwhitewindow.h"
#include "ui_blackandwhitewindow.h"

BlackAndWhiteWindow::BlackAndWhiteWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::BlackAndWhiteWindow)
{
    ui->setupUi(this);
    ui->blueEdit->setText("100");
    ui->redEdit->setText("100");
    ui->greenEdit->setText("100");
    filter = new BlackWhiteFilter;
    bfilter = static_cast<BlackWhiteFilter*>(filter);
    bfilter->setR(100);
    bfilter->setG(100);
    bfilter->setB(100);
}

BlackAndWhiteWindow::~BlackAndWhiteWindow()
{
    delete ui;
}

void BlackAndWhiteWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void BlackAndWhiteWindow::on_okButton_clicked()
{
    emit onOk();
}

void BlackAndWhiteWindow::on_cancelButton_clicked()
{
    emit onCancel();
}

void BlackAndWhiteWindow::on_redEdit_textEdited(const QString &arg1)
{
    int value = ui->redEdit->text().toInt();
    if(value < -100)
    {
        value = -100;
        ui->redEdit->setText(QString::number(value));
    }
    else if(value > 300)
    {
        value = 300;
        ui->redEdit->setText(QString::number(value));
    }
    ui->redSlider->setValue(value);
    bfilter->setR(value);
    apply();
}

void BlackAndWhiteWindow::on_greenEdit_textEdited(const QString &arg1)
{
    int value = ui->greenEdit->text().toInt();
    if(value < -100)
    {
        value = -100;
        ui->greenEdit->setText(QString::number(value));
    }
    if(value > 300)
    {
        value = 300;
        ui->greenEdit->setText(QString::number(value));
    }
    ui->greenSlider->setValue(value);
    bfilter->setG(value);
    apply();
}



void BlackAndWhiteWindow::on_blueEdit_textEdited(const QString &arg1)
{
    int value = ui->blueEdit->text().toInt();
    if(value < -100)
    {
        value = -100;
        ui->blueEdit->setText(QString::number(value));
    }
    if(value > 300)
    {
        value = 300;
        ui->blueEdit->setText(QString::number(value));
    }
    ui->blueSlider->setValue(value);
    bfilter->setB(value);
    apply();
}

void BlackAndWhiteWindow::on_redSlider_sliderReleased()
{
    int value = ui->redSlider->value();
    bfilter->setR(value);
    ui->redEdit->setText(QString::number(value));
    apply();
}

void BlackAndWhiteWindow::on_greenSlider_sliderReleased()
{
    int value = ui->greenSlider->value();
    bfilter->setG(value);
    ui->greenEdit->setText(QString::number(value));
    apply();
}

void BlackAndWhiteWindow::on_blueSlider_sliderReleased()
{
    int value = ui->blueSlider->value();
    bfilter->setB(value);
    ui->blueEdit->setText(QString::number(value));
    apply();
}

void BlackAndWhiteWindow::display()
{
    apply();
}
