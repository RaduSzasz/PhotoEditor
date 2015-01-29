#ifndef BOXBLURWINDOW_H
#define BOXBLURWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "boxblurfilter.h"

namespace Ui {
    class BoxBlurWindow;
}

class BoxBlurWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit BoxBlurWindow(QWidget *parent = 0);
    ~BoxBlurWindow();
protected:
    virtual void apply();
private slots:
    void on_horizontalSlider_sliderReleased();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::BoxBlurWindow *ui;
    BoxBlurFilter *bfilter;

};

#endif // BOXBLURWINDOW_H
