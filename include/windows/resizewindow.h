#ifndef RESIZEWINDOW_H
#define RESIZEWINDOW_H

#include <QDialog>
#include "adjustmentwindow.h"
#include "resizefilter.h"

namespace Ui {
    class ResizeWindow;
}

class ResizeWindow : public AdjustmentWindow
{
    Q_OBJECT

public:
    explicit ResizeWindow(QWidget *parent = 0);
    ~ResizeWindow();
protected:
    virtual void apply();
private slots:
    void on_widthEdit_textEdited(const QString &arg1);

    void on_heightEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

public slots:
    void display();

private:
    Ui::ResizeWindow *ui;
    ResizeFilter *rfilter;
};

#endif // RESIZEWINDOW_H
