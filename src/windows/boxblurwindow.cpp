#include "boxblurwindow.h"
#include "ui_boxblurwindow.h"

BoxBlurWindow::BoxBlurWindow(QWidget *parent) :
    AdjustmentWindow(parent),
    ui(new Ui::BoxBlurWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("0");
    filter = new BoxBlurFilter;
    bfilter = static_cast<BoxBlurFilter*>(filter);
}

BoxBlurWindow::~BoxBlurWindow()
{
    delete ui;
}

void BoxBlurWindow::on_horizontalSlider_sliderReleased()
{
    int value = ui->horizontalSlider->value();
    ui->lineEdit->setText(QString::number(value));
    bfilter->setRadius(value);
    apply();
}

void BoxBlurWindow::apply()
{
    connect(filterApplier, SIGNAL(onFinish()), this, SLOT(ready()));
    filterApplier->run();
}


void BoxBlurWindow::on_okButton_clicked()
{
    emit onOk();
}

void BoxBlurWindow::on_cancelButton_clicked()
{
    emit onCancel();
}

void BoxBlurWindow::on_lineEdit_textEdited(const QString &arg1)
{
    int value = ui->lineEdit->text().toInt();
    ui->horizontalSlider->setValue(value);
    bfilter->setRadius(value);
    apply();
}
