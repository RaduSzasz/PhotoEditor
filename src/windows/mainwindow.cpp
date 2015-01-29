#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gd.h"
#include "color.h"
#include "brightnesswindow.h"
#include "blackandwhitewindow.h"
#include "boxblurwindow.h"
#include "saturationwindow.h"
#include "huewindow.h"
#include "resizewindow.h"
#include "contrastwindow.h"
#include "sharpenwindow.h"
#include <QSettings>
#include <QFileDialog>
#include <QPixmap>
#include <QScrollBar>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PictureManager *instance = PictureManager::getInstance();
    instance->registerPlugin(new JPEGPlugin());
    instance->registerPlugin(new PGMPlugin());
    instance->registerPlugin(new BMPPlugin());
    instance->registerPlugin(new PNGPlugin());
    instance->registerPlugin(new PPMPlugin());
    ui->actionFit_into_screen->setChecked(true);
    ui->actionCentered->setChecked(true);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPicture(Picture *picture)
{
    QPixmap pix;
    int width, height, w, h;
    int sX = ui->scrollArea->horizontalScrollBar()->value();
    int sY = ui->scrollArea->verticalScrollBar()->value();
    if(ui->actionFit_into_screen->isChecked())
    {
        w = this->geometry().width();
        h = this->geometry().height();
        double ratio = ((1.0 * picture->getWidth()) / (1.0 * picture->getHeight()));
        width = 0, height = 0;
        if(ratio > 1)
        {
            if(picture->getWidth() > w - 5)
            {
                width = w - 5;
                height = (int)((1.0 * width) / ratio);
            }
            else
            {
                width = picture->getWidth();
                height = picture->getHeight();
            }
            if(height > h - 25)
            {
                height = h - 25;
                width = (int)((1.0 * height) * ratio);
            }
        }
        else
        {
            if(picture->getHeight() > h - 25)
            {
                height = h - 25;
                width = int((1.0 * height) * ratio);
            }
            else
            {
                width = picture->getWidth();
                height = picture->getHeight();
            }
            if(width > w - 5)
            {
                width = w - 5;
                height = (1.0 * width) / ratio;
            }
        }
    }
    else
    {
        width = picture->getWidth();
        height = picture->getHeight();
    }
    pix = QPixmap::fromImage(picture->getResizedVersion(width, height).toQImage());
    QLabel *label = new QLabel; label->setPixmap(pix);
    ui->scrollArea->setWidget(label);
    ui->scrollArea->horizontalScrollBar()->setValue(sX);
    ui->scrollArea->verticalScrollBar()->setValue(sY);
}

void MainWindow::on_actionOpen_triggered()
{
    QString extensions = "";
    QString allExtensions = "";
    std::string errorMessage;
    PictureManager *instance = PictureManager::getInstance();
    ExtensionList ext = instance->getSupportedFileTypes();
    for(unsigned int i = 0; i < ext.size(); i++)
    {
        extensions += ";;" + QString::fromStdString(ext[i].first) + " (" + QString::fromStdString(ext[i].second) + ")";
        allExtensions += QString::fromStdString(ext[i].second) + " ";
    }
    extensions = "All Picture Files (" + allExtensions + ")" + extensions;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:\\Program Files", extensions);
    instance->setFileName(fileName.toStdString());
    if(instance->loadPicture(*this->pic, fileName.toStdString(), errorMessage))
        showPicture(this->pic);
    else
    {
        QErrorMessage err;
        err.showMessage(QString::fromStdString(errorMessage));
    }
}

void MainWindow::on_actionBrightness_triggered()
{
    w = new BrightnessWindow();
    BrightnessWindow *bw = static_cast<BrightnessWindow*>(w);

    bw->setModal(true);
    bw->setPicture(pic);
    connect(bw, SIGNAL(onRefresh()),this, SLOT(on_refresh()));
    connect(bw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(bw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    bw->show();
}

void MainWindow::on_refresh()
{
    showPicture(w->getPicture());
}

void MainWindow::on_ok()
{
    this->pic = w->getPicture();
    showPicture(this->pic);
    w->close(); delete(w);
}

void MainWindow::on_cancel()
{
    delete(w->getPicture());
    showPicture(this->pic);
    w->close(); delete(w);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionBlack_White_triggered()
{
    w = new BlackAndWhiteWindow();
    BlackAndWhiteWindow *bw = static_cast<BlackAndWhiteWindow*>(w);
    bw->setModal(true);
    bw->setPicture(pic);
    connect(bw, SIGNAL(onRefresh()),this, SLOT(on_refresh()));
    connect(bw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(bw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    connect(this, SIGNAL(dispay()), bw, SLOT(display()));
    emit dispay();
    bw->show();
}

void MainWindow::on_actionBlur_triggered()
{
    w = new BoxBlurWindow();
    BoxBlurWindow *bw = static_cast<BoxBlurWindow*>(w);
    bw->setModal(true);
    bw->setPicture(pic);
    connect(bw, SIGNAL(onRefresh()), this, SLOT(on_refresh()));
    connect(bw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(bw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    bw->show();
}

void MainWindow::on_actionSave_triggered()
{
    PictureManager *instance = PictureManager::getInstance();
    std::string errorMessage;
    instance->savePicture(*this->pic, instance->getFileName(), errorMessage);
}

void MainWindow::on_actionSave_as_triggered()
{
    QString extensions = "";
    QString allExtensions = "";
    std::string errorMessage;
    PictureManager *instance = PictureManager::getInstance();
    ExtensionList ext = instance->getSupportedFileTypes();
    for(unsigned int i = 0; i < ext.size(); i++)
    {
        extensions += ";;" + QString::fromStdString(ext[i].first) + " (" + QString::fromStdString(ext[i].second) + ")";
        allExtensions += QString::fromStdString(ext[i].second) + " ";
    }
    extensions = "All Picture Files (" + allExtensions + ")" + extensions;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image as"), "C:\\Program Files", extensions);
    if(fileName != "")
    {
        instance->setFileName(fileName.toStdString());
        if(!instance->savePicture(*this->pic, instance->getFileName(), errorMessage))
        {
            QErrorMessage err;
            err.showMessage(QString::fromStdString(errorMessage));
        }
    }
}

void MainWindow::on_actionSaturation_triggered()
{
    w = new SaturationWindow;
    SaturationWindow *sw = static_cast<SaturationWindow*>(w);
    sw->setPicture(this->pic);
    sw->setModal(true);
    connect(sw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(sw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    connect(sw, SIGNAL(onRefresh()), this, SLOT(on_refresh()));
    sw->show();
}

void MainWindow::on_actionHue_triggered()
{
    w = new HueWindow;
    HueWindow *hw = static_cast<HueWindow*>(w);
    hw->setPicture(this->pic);
    hw->setModal(true);
    connect(hw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(hw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    connect(hw, SIGNAL(onRefresh()), this, SLOT(on_refresh()));
    hw->show();
}

void MainWindow::on_actionResize_triggered()
{
    w = new ResizeWindow;
    ResizeWindow *rw = static_cast<ResizeWindow*>(w);
    rw->setPicture(this->pic);
    rw->setModal(true);
    connect(rw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(rw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    connect(rw, SIGNAL(onRefresh()), this, SLOT(on_refresh()));
    connect(this, SIGNAL(dispay()), rw, SLOT(display()));
    emit dispay();
    rw->show();
}

void MainWindow::on_actionContrast_triggered()
{
    w = new ContrastWindow;
    ContrastWindow *cw = static_cast<ContrastWindow*>(w);
    cw->setPicture(this->pic);
    cw->setModal(true);
    connect(cw, SIGNAL(onOk()), this, SLOT(on_ok()));
    connect(cw, SIGNAL(onCancel()), this, SLOT(on_cancel()));
    connect(cw, SIGNAL(onRefresh()), this, SLOT(on_refresh()));
    cw->show();
}

void MainWindow::on_actionFit_into_screen_triggered()
{
    if(!ui->actionFit_into_screen->isChecked())
    {
        ui->actionFit_into_screen->setChecked(true);
    }
    ui->actionFull_image->setChecked(false);
    showPicture(this->pic);
}

void MainWindow::on_actionFull_image_triggered()
{
    if(!ui->actionFull_image->isChecked())
    {
        ui->actionFull_image->setChecked(true);
    }
    ui->actionFit_into_screen->setChecked(false);
    showPicture(this->pic);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->scrollArea->setGeometry(ui->scrollArea->geometry().x(), ui->scrollArea->geometry().y(),this->geometry().width(), this->geometry().height() - 20);
    this->showPicture(this->pic);
}

void MainWindow::on_actionLeft_triggered()
{
    if(!ui->actionLeft->isChecked())
    {
        ui->actionLeft->setChecked(true);
    }
    ui->actionCentered->setChecked(false);
    ui->scrollArea->setAlignment(Qt::AlignLeft);
}



void MainWindow::on_actionCentered_triggered()
{
    if(!ui->actionCentered->isChecked())
    {
        ui->actionCentered->setChecked(true);
    }
    ui->actionLeft->setChecked(false);
    ui->scrollArea->setAlignment(Qt::AlignCenter);
}
