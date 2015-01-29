#include "contrastwindow.h"
#include "ui_contrastwindow.h"

ContrastWindow::ContrastWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::ContrastWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    this->filter = new ContrastFilter;
    cfilter = static_cast<ContrastFilter*>(filter);
}

ContrastWindow::~ContrastWindow()
{
    delete ui;
}

void ContrastWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}

void ContrastWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    cfilter->setValue(value);
    ui->lineEdit->setText(QString::number(value));
    apply();
}



void ContrastWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    ui->horizontalSlider->setValue(value);
    cfilter->setValue(value);
    apply();
}

void ContrastWindow::on_okButton_clicked()
{
    emit onOk();
}

void ContrastWindow::on_cancelButton_clicked()
{
    emit onCancel();
}
