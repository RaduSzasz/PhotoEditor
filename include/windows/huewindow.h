#ifndef HUEWINDOW_H
#define HUEWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "huefilter.h"

namespace Ui {
    class HueWindow;
}

class HueWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit HueWindow(QWidget *parent = 0);
    ~HueWindow();
protected:
    virtual void apply();
private slots:
    void on_horizontalSlider_sliderReleased();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::HueWindow *ui;
    HueFilter *hfilter;
};

#endif // HUEWINDOW_H
