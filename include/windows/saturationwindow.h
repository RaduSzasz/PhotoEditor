#ifndef SATURATIONWINDOW_H
#define SATURATIONWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "saturationfilter.h"

namespace Ui {
    class SaturationWindow;
}

class SaturationWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit SaturationWindow(QWidget *parent = 0);
    ~SaturationWindow();
protected:
    virtual void apply();

private slots:
    void on_horizontalSlider_sliderReleased();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SaturationWindow *ui;
    SaturationFilter *sfilter;
};

#endif // SATURATIONWINDOW_H
