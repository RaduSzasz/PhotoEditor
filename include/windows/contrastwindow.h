#ifndef CONTRASTWINDOW_H
#define CONTRASTWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "contrastfilter.h"

namespace Ui {
    class ContrastWindow;
}

class ContrastWindow : public AdjustmentWindow
{
    Q_OBJECT

protected:
    virtual void apply();

public:
    explicit ContrastWindow(QWidget *parent = 0);
    ~ContrastWindow();

private slots:
    void on_horizontalSlider_sliderReleased();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ContrastWindow *ui;
    ContrastFilter *cfilter;
};

#endif // CONTRASTWINDOW_H
