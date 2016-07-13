#include "tcpSocket.h"


cv::Mat tcpTransport::frame1;
tcpTransport::tcpTransport()
{
    //this->tcpServer = new QTcpServer();
    this->tcpSocket = new QTcpSocket();
    //connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    datasize = 0;
    //newListen();
    //connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    //connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    //connect(&timer1,SIGNAL(timeout()),this,SLOT(sendData()));//定时器作为信号，时间一到，触发发送图片槽函数
}

tcpTransport::~tcpTransport()
{

}

//void tcpTransport::on_send_clicked()
//{
//    //this->tcpSocket->write(ui->message->text().toLatin1());
//    //sendData();
//    //timer1.start();
//}

//void tcpTransport::on_stop_clicked()
//{
//    //timer1.stop();
//}

//void tcpTransport::newListen()
//{
//    if (!tcpServer->listen(QHostAddress::Any,6666))
//    {
//        qDebug()<<tcpServer->errorString();
//        //close();
//        return;

//    }
//}

//void tcpTransport::acceptConnection()
//{
//    tcpSocket = tcpServer->nextPendingConnection();
//    qDebug()<<"connected!";

//}


//void tcpTransport::displayError(QAbstractSocket::SocketError)
//{
//    qDebug()<<tcpServer->errorString();
//    tcpSocket->close();

//}

void tcpTransport::sendData(Mat &frame)
{

    //timer1.stop();//发送图片前停止定时器

//    Mat frame;
//    tempImg = cvQueryFrame(capture);//c++接口无法打开视频，利用c接口中转一下，所以需要将iplimage转换为Mat
//    if (tempImg)
//        frame = Mat(tempImg);
    cv::Mat sendFrame;
    cvtColor(frame, sendFrame, CV_BGR2RGB);
    QImage image1 = QImage((uchar*)(sendFrame.data), sendFrame.cols, sendFrame.rows, QImage::Format_RGB888);


    QByteArray Data;
    QBuffer buffer;
    QDataStream out(&Data,QIODevice::WriteOnly);

    //displayvideo();
    image1.save(&buffer,"jpg");

   //out.setVersion(QDataStream::Qt_4_6);
    out<<(quint32)buffer.data().size();
    Data.append(buffer.data());

    tcpSocket->write(Data);

    //delete image;
    Data.resize(0);
    buffer.reset();

    //timer1.start();//发送图片结束，打开定时器

}

void tcpTransport::revData()
{
    //qDebug()<<"get!";
    //客服端第一次先接收数据流中图片大小信息
    if(datasize == 0)
    {
        QDataStream in(tcpSocket);
        //in.setVersion( QDataStream::Qt_4_6);

        if(tcpSocket->bytesAvailable() < sizeof(quint32))
        {
          return;
        }

        in>>datasize;
    }
    qDebug()<<datasize;
   //然后根据图片大小信息接收JPG格式图片

    if(datasize > tcpSocket->bytesAvailable())
    {
        return;
    }

    //显示接收到的图片
    //displayvideo(frame1);
    //imshow("inner",frame1);

    QByteArray Data = tcpSocket->read(datasize);
    QBuffer buffer(&Data);
    buffer.open( QIODevice::ReadOnly);

    QImageReader reader(&buffer, "jpg");
    QImage image = reader.read();

    image = image.convertToFormat(QImage::Format_RGB888);

    cv::Mat testMat;
    QImage2cvMat(image,frame1);
    //imshow("inner frame",frame);

    //QImage2cvMat(image);

    //qDebug()<<"dis";

//    ui->label->setScaledContents(true);
//    ui->label->setPixmap(QPixmap::fromImage(image,Qt::AutoColor));
//    ui->label->resize(image.size());

    //if(datasize != 0) ui->label_2->setText(QString::number(datasize));

    //将datasize图片大小信息重置0为下一接收做准备。

    datasize = 0;
    imshow("inner frame",frame1);
}

void tcpTransport::displayvideo(cv::Mat &frame)
{

    QByteArray Data = tcpSocket->read(datasize);
    QBuffer buffer(&Data);
    buffer.open( QIODevice::ReadOnly);

    QImageReader reader(&buffer, "jpg");
    QImage image = reader.read();

    image = image.convertToFormat(QImage::Format_RGB888);

    cv::Mat testMat;
    QImage2cvMat(image,frame);
    //imshow("inner frame",frame);

    //QImage2cvMat(image);
    imshow("inner frame",frame);
    //qDebug()<<"dis";

//    ui->label->setScaledContents(true);
//    ui->label->setPixmap(QPixmap::fromImage(image,Qt::AutoColor));
//    ui->label->resize(image.size());

    //if(datasize != 0) ui->label_2->setText(QString::number(datasize));

    //将datasize图片大小信息重置0为下一接收做准备。

    datasize = 0;
}

void tcpTransport::QImage2cvMat(QImage image,cv::Mat &mat)
{
    //qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
}
