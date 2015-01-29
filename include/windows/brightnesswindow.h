#ifndef BRIGHTNESSWINDOW_H
#define BRIGHTNESSWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "brightnessfilter.h"
#include "picturemanager.h"

namespace Ui {
    class BrightnessWindow;
}

class BrightnessWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit BrightnessWindow(QWidget *parent = 0);
    ~BrightnessWindow();

protected:
    virtual void apply();
private slots:

    void on_horizontalSlider_sliderReleased();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::BrightnessWindow *ui;
    BrightnessFilter* bfilter;
};

#endif // BRIGHTNESSWINDOW_H
