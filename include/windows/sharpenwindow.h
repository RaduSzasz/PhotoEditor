#ifndef SHARPENWINDOW_H
#define SHARPENWINDOW_H

#include <QDialog>
#include "sharpenfilter.h"
#include "adjustmentwindow.h"

namespace Ui {
    class SharpenWindow;
}

class SharpenWindow : public AdjustmentWindow
{
    Q_OBJECT
protected:
    virtual void apply();
public:
    explicit SharpenWindow(QWidget *parent = 0);
    ~SharpenWindow();

private slots:
    void on_horizontalSlider_sliderReleased();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SharpenWindow *ui;
    SharpenFilter *sfilter;
};

#endif // SHARPENWINDOW_H
