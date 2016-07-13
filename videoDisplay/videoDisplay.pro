#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T15:41:36
#
#-------------------------------------------------

QT       += core gui network

INCLUDEPATH += F:\opencv2.4.7\opencv\build\include
INCLUDEPATH += F:\opencv2.4.7\opencv\build\include\opencv
INCLUDEPATH += F:\opencv2.4.7\opencv\build\include\opencv2

LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_calib3d2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_contrib2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_core2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_features2d2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_flann2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_gpu2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_highgui2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_imgproc2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_legacy2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_ml2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_nonfree2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_objdetect2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_ocl2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_photo2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_stitching2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_superres2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_ts2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_video2410d.lib
LIBS +=F:\opencv2.4.7\opencv\build\x86\vc10\lib\opencv_videostab2410d.lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoDisplay
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myAlgorithm.cpp \
    detect.cpp \
    tcpSocket.cpp

HEADERS  += mainwindow.h \
    myAlgorithm.h \
    detect.h \
    tcpSocket.h

FORMS    += mainwindow.ui
