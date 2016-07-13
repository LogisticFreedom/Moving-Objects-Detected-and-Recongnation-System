#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("基于OpenCV单目标运动物体检测与识别系统设计");
    setWindowIcon(QIcon("F:/qt_test/videoDisplay/videoDisplay/cat.jpg"));
    //capture = new CvCapture();
    //capture = cvCaptureFromFile(fileName);
    //divog = new DIVoG();
    //DIVoG divog;
    //this->cap.open(0);

    findFlag = 0; //初始化识别标志位
    sendFlag = 0;
    receiveFlag = 0;
    learnRate = 0;

    if (capture)
    {
        time1.setInterval(1);
        algorithmFlag = 0;
    }
    else
    {
        qDebug()<<"not open!";
    }

    //connect(&time1, &QTimer::timeout, this, &MainWindow::updateImage);
    //connect(this,SIGNAL(startUpdate()),this,SLOT(updateImage()));
    connect(&time1, &QTimer::timeout, this, &MainWindow::updateFPS);
    //connect(&time1, &QTimer::timeout, &newTransport,SLOT(revData()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(this,SIGNAL(detectSuccess()),this,SLOT(showAns()));
    connect(this,SIGNAL(detectFailed()),this,SLOT(showAns()));
    connect(this,SIGNAL(startSend(Mat &)),&newTransport,SLOT(sendData(Mat &)));
    //connect(this,SIGNAL(startRecv(Mat &)),&newTransport,SLOT(revData(Mat &)));


    //connect(newTransport.tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    //connect(&time1,SIGNAL(timeout()),this,SLOT(revData()));
    datasize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    cvReleaseCapture(&capture);
}



void MainWindow::paintEvent(QPaintEvent *)
{


    QImage image1 = QImage((uchar*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->originalVideo->setPixmap(QPixmap::fromImage(image1));
    ui->originalVideo->resize(image1.size());
    ui->originalVideo->show();

    QImage image2 = QImage((uchar*)(sailencyMap.data), sailencyMap.cols, sailencyMap.rows, QImage::Format_Indexed8);
    ui->sailencyMapVideo->setPixmap(QPixmap::fromImage(image2));
    ui->sailencyMapVideo->resize(image2.size());
    ui->sailencyMapVideo->show();

    QImage image3 = QImage((uchar*)(motionMap.data), motionMap.cols, motionMap.rows, QImage::Format_Indexed8);
    ui->motionVideo->setPixmap(QPixmap::fromImage(image3));
    ui->motionVideo->resize(image3.size());
    ui->motionVideo->show();

}

void MainWindow::updateImage()
{
    //cap>>frame;
    //time1.stop();
    if (receiveFlag == 0)
    {
        tempImg = cvQueryFrame(capture);//c++接口无法打开视频，利用c接口中转一下，所以需要将iplimage转换为Mat
        if (tempImg)
            rawFrame = Mat(tempImg);
        else
        {
            time1.stop();
            return;
        }
    }

    if (!rawFrame.empty())
       cv::resize(rawFrame,frame,Size(320,240));
    else
        qDebug()<<"no images!";

   // equalizeHist(frame,frame2);
    if(!frame.empty())
    {
        //emit startSend(frame);

        double t=(double)cvGetTickCount();
        switch (algorithmFlag)
        {
            case 0:
                divog.trackObject(frame,sailencyMap,motionMap);
                findFlag = divog.getFindAns();
                break;
            case 1:
                sr.getSRsailencyMap(frame,sailencyMap,motionMap);
                findFlag = sr.getFindAns();
                break;
            case 2:
                myft.getFTmap(frame,sailencyMap,motionMap,learnRate);
                findFlag = myft.getFindAns();
                break;
            case 3:
                itti.getSailencyMapItti(frame,sailencyMap,motionMap);
                findFlag = itti.getFindAns();
                break;
            case 4:
                lc.getLCsailencyMap(frame,sailencyMap,motionMap);
                findFlag = lc.getFindAns();
                break;
            case 5:
                gmm.getGMMMap(frame,motionMap);
                findFlag = gmm.getFindAns();
                //break;
            case 6:
                gmm.getGrayGMMMap(frame,motionMap);
                findFlag = gmm.getFindAns();

        }
        if (sendFlag == 1)
            emit startSend(frame);
        if (findFlag == 1)
            emit detectSuccess();
        else
            emit detectFailed();
        t=((double)cvGetTickCount() - t)/(cvGetTickFrequency()*1000);
        fpsNum = 1000/t;
        //qDebug()<<fpsNum;

        cvtColor(frame, frame, CV_BGR2RGB);
        //getSailencyMap(frame,sailencyMap);
        //qDebug()<<sailencyMap.elemSize();
        //qDebug()<<frame.elemSize();
        //floatMap.convertTo(sailencyMap,CV_8U);
        //cvtColor(sailencyMap, sailencyMap, CV_BGR2RGB);
        this->update();
    }
    //time1.start();

}

void MainWindow::on_connect_clicked()
{
    newTransport.tcpSocket->abort();
    newTransport.tcpSocket->connectToHost("192.168.1.102",8086);
}


void MainWindow::on_playButton_clicked()
{
    time1.start();
}

void MainWindow::on_stopButton_clicked()
{
    time1.stop();
}

void MainWindow::on_selectButton_clicked()
{
    algorithmFlag = ui->algorithmChoice->currentIndex();
}

void MainWindow::on_transport_clicked()
{
    sendFlag = 1;
}

void MainWindow::on_stopSend_clicked()
{
    sendFlag = 0;
}

void MainWindow::on_StartDetectButton_clicked()
{
    divog.setFlag(1);
    sr.setFlag(1);
    myft.setFlag(1);
    itti.setFlag(1);
}

void MainWindow::on_ApplyDetectButton_clicked()
{
    //motionMap.setTo(0);
    int index = ui->detectChoice->currentIndex();
    divog.setMethodIndex(index);
    sr.setMethodIndex(index);
    myft.setMethodIndex(index);
    itti.setMethodIndex(index);
}

void MainWindow::on_stopDetectButton_clicked()
{
    divog.setFlag(0);
    sr.setFlag(0);
    myft.setFlag(0);
    itti.setFlag(0);

}

void MainWindow::openFile()
{
    learnRate = 0.01;
    connect(&time1, &QTimer::timeout, this, &MainWindow::updateImage);
    QString fileFull = QFileDialog::getOpenFileName(this,"Open","D:/");
    //QFileInfo fi = QFileInfo(fileFull);
    //QString fileName1 = fi.fileName().trimmed();
    //file_path = fi.absolutePath();
    const QByteArray text = fileFull.toLocal8Bit();
    fileName = text.data();
    capture = cvCaptureFromFile(fileName);
}

void MainWindow::on_openVideoButton_clicked()
{
    learnRate = 0.1;
    connect(&time1, &QTimer::timeout, this, &MainWindow::updateImage);
    disconnect(newTransport.tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    receiveFlag = 0;
    capture = cvCaptureFromCAM(0);
}

void MainWindow::updateFPS()
{
    ui->fpsLCD->display(fpsNum);
}

void MainWindow::showAns()
{
    QFont ft;
    ft.setPointSize(18);
    ui->showClassify->setFont(ft);
    if (findFlag == 1)
        ui->showClassify->setText("This is a car!");
    else
        ui->showClassify->setText("No Objects!");
}

void MainWindow::on_openRemote_clicked()
{
    learnRate = 0.1;

    connect(newTransport.tcpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    disconnect(&time1, &QTimer::timeout, this, &MainWindow::updateImage);
    receiveFlag = 1;
    QString s = "python camera2.py";
    newTransport.tcpSocket->write(s.toLatin1());
    //fileName = "d:/cam.avi";
    //connect(&time1, &QTimer::timeout, this, &MainWindow::updateImage);
    //capture = cvCaptureFromFile("D:/cam.avi");
}



void MainWindow::revData()
{
    //客服端第一次先接收数据流中图片大小信息
    if(datasize == 0)
    {
        QDataStream in(newTransport.tcpSocket);
        //in.setVersion( QDataStream::Qt_4_6);

        if(newTransport.tcpSocket->bytesAvailable() < sizeof(quint32))
        {
          return;
        }

        in>>datasize;
    }
    //qDebug()<<datasize;
   //然后根据图片大小信息接收JPG格式图片

    if(datasize > newTransport.tcpSocket->bytesAvailable())
    {
        return;
    }

    Data = newTransport.tcpSocket->read(datasize);

    QBuffer buffer(&Data);
    buffer.open( QIODevice::ReadOnly);

    QImageReader reader(&buffer, "jpg");
    QImage image = reader.read();

    image = image.convertToFormat(QImage::Format_RGB888);

    frame1 = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
    cv::cvtColor(frame1, frame1, CV_BGR2RGB);
    //rawFrame = frame1.clone();
    //frame1.copyTo(rawFrame);
    //将datasize图片大小信息重置0为下一接收做准备。

    datasize = 0;
    //imshow("inner frame",frame1);

    //if (!rawFrame.empty())
       cv::resize(frame1,frame,Size(320,240));
    //else
        //qDebug()<<"no images!";

   // equalizeHist(frame,frame2);
    if(!frame.empty())
    {
        //emit startSend(frame);

        double t=(double)cvGetTickCount();
        switch (algorithmFlag)
        {
            case 0:
                divog.trackObject(frame,sailencyMap,motionMap);
                findFlag = divog.getFindAns();
                break;
            case 1:
                sr.getSRsailencyMap(frame,sailencyMap,motionMap);
                findFlag = sr.getFindAns();
                break;
            case 2:
                myft.getFTmap(frame,sailencyMap,motionMap,learnRate);
                findFlag = myft.getFindAns();
                break;
            case 3:
                itti.getSailencyMapItti(frame,sailencyMap,motionMap);
                findFlag = itti.getFindAns();
                break;
            case 4:
                lc.getLCsailencyMap(frame,sailencyMap,motionMap);
                findFlag = lc.getFindAns();
                break;
            case 5:
                gmm.getGMMMap(frame,motionMap);
                findFlag = gmm.getFindAns();
                //break;
            case 6:
                gmm.getGrayGMMMap(frame,motionMap);
                findFlag = gmm.getFindAns();

        }
        if (sendFlag == 1)
            emit startSend(frame);
        if (findFlag == 1)
            emit detectSuccess();
        else
            emit detectFailed();
        t=((double)cvGetTickCount() - t)/(cvGetTickFrequency()*1000);
        fpsNum = 1000/t;
        //qDebug()<<fpsNum;

        cvtColor(frame, frame, CV_BGR2RGB);
        //getSailencyMap(frame,sailencyMap);
        //qDebug()<<sailencyMap.elemSize();
        //qDebug()<<frame.elemSize();
        //floatMap.convertTo(sailencyMap,CV_8U);
        //cvtColor(sailencyMap, sailencyMap, CV_BGR2RGB);
        this->update();
    }
}







