#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdio>

#include <QDebug>
#include "detect.h"
using namespace cv;
using namespace std;

class findObject
{
public:
    findObject();
    ~findObject();
    void getObject(const Mat &binImg, Mat &srcImg);
    void setFlag(bool flag);
    void setMethodIndex(int index);
    bool getFindAns();
    DetectHaar detect;
private:
    int methodIndex;
    bool startFlag;
    bool findAns;

};

class DIVoG:public findObject
{
private:
    BackgroundSubtractorMOG *bgSubtractor;

    void getUpImg(Mat &U1Img,Mat &UnImg,int n);
    void getDownImg(Mat &UnImg,Mat &D1Img,int n);
    void MiR(Mat &U1Img,Mat &D1Img,Mat &ansImg);
    void getSailencyMap(Mat &srcImg,Mat &sailencyMap);
    //void getObject(Mat &binImg,Mat &srcImg);
public:
    DIVoG();
    ~DIVoG();
    void trackObject(Mat &srcImg, Mat &sailencyMap, Mat &mask);

};


class SR:public findObject
{
private:
    BackgroundSubtractorMOG *bgSubtractor;
    void calculateSR(Mat &image,Mat &saliencyMap);
    void computeBinaryMap( const Mat& saliencyMap, Mat& BinaryMap);

public:
    SR();
    ~SR();
    void getSRsailencyMap(Mat &frame, Mat &sailencyMap, Mat &showBinImg);


};

class myFT:public findObject
{
private:
    BackgroundSubtractorMOG *bgSubtractor;
    void getSailencyMapFT(Mat &srcImg,Mat &sailencyMap);
public:
    myFT();
    ~myFT();
    void getFTmap(Mat &frame, Mat &sailencyMap, Mat &showBinImg, double learnRate);

};

class IttiModel:public findObject
{

private:
    BackgroundSubtractorMOG *bgSubtractor;
    int pyrNum;
    int opNum;
    int STEP;
    int opSigama ;
    int GABOR_R ;
    //int pairs[6][2];
    void normalizeRange(Mat& image);
    void createPyrmaid(Mat& srcImg,int pyrNum,vector<Mat> &pyrList);
    void trimPeaks(Mat& image,int step);
    void getGrayPyrmaid(Mat& srcImg,int pyrNum,vector<Mat> &grayPyrMaid);
    void getGraySailencyMap(vector<Mat> &grayPyrMaid,Mat& ansImg,int opSigama);
    void getColorFeatureMap(Mat& srcImg,vector<Mat> &colorFeatureMap);
    void getColorSailencyMap(vector<Mat> &colorFeatureMap,Mat& ansImg,int opSigama);
    void getOrientionSailencyMap(Mat& image,Mat& ansImg);
    void buildCenterSurroundPyramid(const vector<Mat>& pyramid);
    void getSailencyMap(Mat &srcImg,Mat &sailencyMap);
public:
    IttiModel();
    ~IttiModel();

    void getSailencyMapItti(Mat &frame,Mat &sailnecyMap,Mat &mask);
};

class LC:public findObject
{
public:
    LC();
    ~LC();
    void getLCsailencyMap(Mat &frame, Mat &sailencyMap, Mat &showBinImg);
private:
    BackgroundSubtractorMOG *bgSubtractor;
    void LCOperation(Mat &srcImg, Mat &sailencyMap);


};

class originalGMM:public findObject
{
public:
    originalGMM();
    ~originalGMM();
    void getGMMMap(Mat &frame,Mat &showBinImg);
    void getGrayGMMMap(Mat &frame, Mat &showBinImg);
private:
    BackgroundSubtractorMOG *bgSubtractor;

};

#endif // ALGORITHM_H
