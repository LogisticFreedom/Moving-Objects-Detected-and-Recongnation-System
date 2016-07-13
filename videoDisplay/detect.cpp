#include "detect.h"

DetectHaar::DetectHaar()
{

}

DetectHaar::~DetectHaar()
{

}

void DetectHaar::loadXML(int flag)
{

    if (flag == 1)
    {
        if (fenleiqi.load("F:\\qt_test\\videoDisplay\\videoDisplay\\haarcascade_upperbody.xml"))
            qDebug()<<"human classifier has been loaded!";
    }
    if (flag == 0)
    {
        if (fenleiqi.load("F:\\qt_test\\videoDisplay\\videoDisplay\\model.xml"))\
            qDebug()<<"car classifier has been loaded!";
    }

}

bool DetectHaar::detectAndDisplay(Mat &frame)
{
    std::vector<Rect> objects;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    fenleiqi.detectMultiScale( frame_gray, objects, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    qDebug()<<objects.size();
    if (objects.size() > 0)
        return 1;
    else
        return 0;
//    //cout<<objects.size();
//    for( size_t i = 0; i < objects.size(); i++ )
//    {
//        Point center( int(objects[i].x + objects[i].width*0.5), int(objects[i].y + objects[i].height*0.5) );
//        ellipse( frame, center, Size( int(objects[i].width*0.5), int(objects[i].height*0.5)), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
//    }
}
