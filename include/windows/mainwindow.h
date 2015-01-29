#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "picture.h"
#include "filter.h"
#include "picturemanager.h"
#include "jpegplugin.h"
#include "pgmplugin.h"
#include "bmpplugin.h"
#include "pngplugin.h"
#include "ppmplugin.h"
#include "adjustmentwindow.h"
#include "brightnesswindow.h"
#include <QScrollArea>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void dispay();
private slots:

    void on_actionOpen_triggered();

    void on_actionBrightness_triggered();

    void on_actionExit_triggered();

    void on_actionBlack_White_triggered();

    void on_actionBlur_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionSaturation_triggered();

    void on_actionHue_triggered();

    void on_actionResize_triggered();

    void on_actionContrast_triggered();

    void on_actionFit_into_screen_triggered();

    void on_actionFull_image_triggered();

    virtual void resizeEvent(QResizeEvent *);

    void on_actionLeft_triggered();

    void on_actionCentered_triggered();

public slots:

    void on_refresh();

    void on_ok();

    void on_cancel();

private:
    Ui::MainWindow *ui;
    Picture *pic;
    AdjustmentWindow *w;
    void showPicture(Picture* picture);
};

#endif // MAINWINDOW_H
