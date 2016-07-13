#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <opencv2/opencv.hpp>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QImageReader>
using namespace cv;


class tcpTransport:public QObject
{
    Q_OBJECT
public:
    tcpTransport();
    ~tcpTransport();
    static cv::Mat frame1;
    QTcpSocket *tcpSocket;

private:
    int datasize;
    void displayvideo(cv::Mat &frame);
    void QImage2cvMat(QImage image, cv::Mat &mat);

    //QTcpServer *tcpServer;

private slots:
    //void on_send_clicked();
    //void on_stop_clicked();
    //void newListen();
    //void acceptConnection();
    //void displayError(QAbstractSocket::SocketError);

    void sendData(Mat &frame);
    void revData();
};




#endif // TCPSOCKET_H
