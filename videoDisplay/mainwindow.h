#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixMap>
#include <QLabel>
#include <QImage>
#include <QPaintEvent>
#include <opencv2\opencv.hpp>
#include <string>
#include <QFileDialog>
#include <QString>
#include "myAlgorithm.h"
#include "tcpSocket.h"
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);

private:
    Ui::MainWindow *ui;
    CvCapture *capture;
    //VideoCapture cap;

    Mat frame;
    Mat rawFrame;
    Mat sailencyMap;
    Mat motionMap;
    IplImage *tempImg;

    QTimer time1;

    DIVoG divog;
    SR sr;
    myFT myft;
    IttiModel itti;
    LC lc;
    originalGMM gmm;

    int algorithmFlag;
    const char *fileName;
    int videoSource;
    double fpsNum;
    double learnRate;

    bool findFlag;
    bool sendFlag;
    bool receiveFlag;

    tcpTransport newTransport;


    Mat frame1;
    int datasize;
    QByteArray Data;
    //void displayvideo(cv::Mat &frame);
    //void QImage2cvMat(QImage &image, cv::Mat &mat);

private slots:
    void updateImage();
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_selectButton_clicked();
    void on_transport_clicked();
    void on_stopSend_clicked();
    void on_openVideoButton_clicked();
    void on_StartDetectButton_clicked();
    void on_ApplyDetectButton_clicked();
    void on_stopDetectButton_clicked();
    void on_connect_clicked();
    void on_openRemote_clicked();
    void openFile();
    void updateFPS();
    void showAns();


    void revData();

signals:
    void detectSuccess();
    void detectFailed();
    void startSend(Mat &frame);


};

#endif // MAINWINDOW_H
