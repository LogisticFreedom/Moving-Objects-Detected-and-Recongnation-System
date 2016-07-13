#ifndef DETECT_H
#define DETECT_H

#include <opencv2/opencv.hpp>
#include <QDebug>
using namespace cv;

class DetectHaar
{

public:
    DetectHaar();
    ~DetectHaar();
    bool detectAndDisplay(Mat &frame);
    void loadXML(int flag);
private:
    CascadeClassifier fenleiqi;



};


#endif // DETECT_H
