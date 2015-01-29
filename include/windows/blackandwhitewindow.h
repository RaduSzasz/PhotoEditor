#ifndef BLACKANDWHITEWINDOW_H
#define BLACKANDWHITEWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "blackwhitefilter.h"
#include "picturemanager.h"

namespace Ui {
    class BlackAndWhiteWindow;
}

class BlackAndWhiteWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit BlackAndWhiteWindow(QWidget *parent = 0);
    ~BlackAndWhiteWindow();

protected:
    virtual void apply();
public slots:
    void display();
private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_redEdit_textEdited(const QString &arg1);

    void on_greenEdit_textEdited(const QString &arg1);

    void on_blueEdit_textEdited(const QString &arg1);

    void on_redSlider_sliderReleased();

    void on_greenSlider_sliderReleased();

    void on_blueSlider_sliderReleased();

private:
    Ui::BlackAndWhiteWindow *ui;
    BlackWhiteFilter *bfilter;
};

#endif // BLACKANDWHITEWINDOW_H
