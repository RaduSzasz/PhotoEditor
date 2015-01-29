#-------------------------------------------------
#
# Project created by QtCreator 2011-08-20T01:00:28
#
#-------------------------------------------------

QT       += core gui
LIBS       += -lgd -lgomp

TARGET = poza
TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp

INCLUDEPATH += include
INCLUDEPATH += include/filters
INCLUDEPATH += include/windows
INCLUDEPATH += include/plugins


SOURCES += src/main.cpp\
        src/windows/mainwindow.cpp \
    src/picture.cpp \
    src/color.cpp \
    src/filters/filter.cpp \
    src/plugins/formatplugin.cpp \
    src/picturemanager.cpp \
    src/plugins/jpegplugin.cpp \
    src/plugins/pgmplugin.cpp \
    src/plugins/bmpplugin.cpp \
    src/plugins/pngplugin.cpp \
    src/plugins/ppmplugin.cpp \
    src/filters/threadedfilterapplier.cpp \
    src/filters/boxblurfilter.cpp \
    src/filters/blackwhitefilter.cpp \
    src/filters/brightnessfilter.cpp \
    src/windows/adjustmentwindow.cpp \
    src/windows/brightnesswindow.cpp \
    src/windows/blackandwhitewindow.cpp \
    src/windows/progressbarwindow.cpp \
    src/windows/boxblurwindow.cpp \
    src/filters/saturationfilter.cpp \
    src/windows/saturationwindow.cpp \
    src/filters/huefilter.cpp \
    src/windows/huewindow.cpp \
    src/windows/resizewindow.cpp \
    src/filters/resizefilter.cpp \
    src/filters/contrastfilter.cpp \
    src/windows/contrastwindow.cpp

HEADERS  += include/windows/mainwindow.h \
    include/picture.h \
    include/color.h \
    include/filters/filter.h \
    include/plugins/formatplugin.h \
    include/picturemanager.h \
    include/plugins/jpegplugin.h \
    include/plugins/pgmplugin.h \
    include/plugins/bmpplugin.h \
    include/plugins/pngplugin.h \
    include/plugins/ppmplugin.h \
    include/filters/threadedfilterapplier.h \
    include/filters/boxblurfilter.h \
    include/filters/blackwhitefilter.h \
    include/filters/brightnessfilter.h \
    include/windows/adjustmentwindow.h \
    include/windows/brightnesswindow.h \
    include/windows/blackandwhitewindow.h \
    include/windows/progressbarwindow.h \
    include/windows/boxblurwindow.h \
    include/filters/saturationfilter.h \
    include/windows/saturationwindow.h \
    include/filters/huefilter.h \
    include/windows/huewindow.h \
    include/windows/resizewindow.h \
    include/filters/resizefilter.h \
    include/filters/contrastfilter.h \
    include/windows/contrastwindow.h

FORMS    += ui/mainwindow.ui \
    ui/brightnesswindow.ui \
    ui/blackandwhitewindow.ui \
    ui/progressbarwindow.ui \
    ui/boxblurwindow.ui \
    ui/saturationwindow.ui \
    ui/huewindow.ui \
    ui/resizewindow.ui \
    ui/contrastwindow.ui


































































































