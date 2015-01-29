#ifndef PROGRESSBARWINDOW_H
#define PROGRESSBARWINDOW_H

#include <QDialog>

namespace Ui {
    class ProgressBarWindow;
}

class ProgressBarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressBarWindow(QWidget *parent = 0);
    void setMaxValue(int value);
    ~ProgressBarWindow();
public slots:
        void update(int progress);
private:
    Ui::ProgressBarWindow *ui;
};

#endif // PROGRESSBARWINDOW_H
