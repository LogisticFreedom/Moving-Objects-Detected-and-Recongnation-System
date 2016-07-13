#include "myAlgorithm.h"


findObject::findObject()
{
    detect.loadXML(0);
    startFlag = 0;
    findAns = 0;
}

findObject::~findObject()
{

}

void findObject::setFlag(bool flag)
{
    startFlag = flag;
}

void findObject::setMethodIndex(int index)
{
    methodIndex = index;
    detect.loadXML(index);
}

bool findObject::getFindAns()
{
    return findAns;
}

void findObject::getObject(const Mat &binImg, Mat &srcImg)
{

    vector< vector<Point> > contours ;
    if(binImg.data)
    {
        findContours(binImg,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    }
    else
    {
        qDebug() << "It's a black image, so I'm not going to do anything..." ;
        return;
    }


    if(contours.size() > 1)
    {
        // 寻找最大连通域
        double maxArea = 0;
        vector <Point> maxContour;
        for(size_t i = 0; i < contours.size(); i++)
        {
            double area = contourArea(contours[i]);
            if (area > maxArea)
            {
                maxArea = area;
                maxContour = contours[i];
            }
        }
        // 将轮廓转为矩形框,这里要先做一下判断，证明确实存在最大连通域，否则会崩溃
        Rect maxRect;
        Mat ROI;
        if (maxContour.size()!=0)
        {
             //detect.detectAndDisplay(srcImg);
             maxRect = boundingRect(maxContour);
             //detect.detectAndDisplay(srcImg);
             //Point *center = new Point(maxRect.x+maxRect.width/2,maxRect.y+maxRect.height/2);
             //qDebug()<<maxRect.x+maxRect.width/2<<maxRect.y+maxRect.height/2;
             //输出坐标，可以用作给下位机发信号
             if (startFlag && (0 <= maxRect.x)
                 && 0 <= maxRect.width
                 && maxRect.x + maxRect.width <= srcImg.cols
                 && 0 <= maxRect.y
                 && 0 <= maxRect.height
                 && maxRect.y + maxRect.height <= srcImg.rows){
                 // box within the image plane
                 ROI = srcImg(maxRect);
                 findAns = detect.detectAndDisplay(ROI);
             }
        }


//        // 显示连通域

//        //binImg.copyTo(result1);
//        //binImg.copyTo(result2);

//        //for (size_t i = 0; i < contours.size(); i++)
//        {
//            //Rect r = cv::boundingRect(contours[i]);
//            //rectangle(binImg, r, cv::Scalar(255));
//        }

        rectangle(srcImg, maxRect, cv::Scalar(255,0,0));
    }
}


DIVoG::DIVoG()
{
    bgSubtractor = new BackgroundSubtractorMOG(20,10,0.5,0);
}

DIVoG::~DIVoG()
{

}


void DIVoG::getDownImg(Mat &UnImg, Mat &D1Img, int n)
{
    Mat tempImg;
    Mat srcImg = UnImg;
    for (int i = 0;i < n;i++)
    {
        pyrUp(srcImg,tempImg);
        srcImg = tempImg;
    }
    D1Img = tempImg;
}
void DIVoG::getUpImg(Mat &U1Img, Mat &UnImg, int n)
{
    Mat tempImg;
    Mat srcImg = U1Img;
    for (int i = 0;i < n;i++)
    {
        pyrDown(srcImg,tempImg);
        srcImg = tempImg;
    }

    UnImg = tempImg;
}
void DIVoG::MiR(Mat &U1Img, Mat &D1Img, Mat &ansImg)
{
    //D1Img += Scalar::all(1); //预防除零错，但是在测试时还没有发现明显的除零错误
    //U1Img += Scalar::all(1);
    Mat tempImg1,tempImg2;
    divide(U1Img,D1Img,tempImg1);
    divide(D1Img,U1Img,tempImg2);
    min(tempImg1,tempImg2,ansImg);
    ansImg = 1-ansImg;
    blur(ansImg,ansImg,Size(5,5));
}

void DIVoG::getSailencyMap(Mat &srcImg, Mat &sailencyMap)
{
    Mat grayImg;
    cvtColor(srcImg,grayImg,CV_RGB2GRAY);
    equalizeHist(grayImg,grayImg);
    Mat_<float> U1Img=grayImg/255.0f;


    Mat UnImg,D1Img;
    getUpImg(U1Img,UnImg,5);
    //cout<<U1Img.size()<<endl;
    getDownImg(UnImg,D1Img,5);
    //cout<<D1Img.size()<<endl;
    Mat newU1Img;
    Mat floatSailencyMap;
    if (U1Img.size() != D1Img.size()) //视频测试时发现抽样回的图像可能和原图像大小不一致，在此做判断，强行使尺寸一致
    {
        resize(U1Img,newU1Img,D1Img.size());
        MiR(newU1Img,D1Img,floatSailencyMap);
    }
    else
    {
        MiR(U1Img,D1Img,floatSailencyMap);
    }
    floatSailencyMap.convertTo(sailencyMap,CV_8U,255.0);
}



void DIVoG::trackObject(Mat &srcImg, Mat &sailencyMap, Mat &showBinImg)
{
    Mat mask;
    getSailencyMap(srcImg,sailencyMap);
    (*bgSubtractor)(sailencyMap,mask,0.01);
    showBinImg = mask.clone();
    getObject(mask,srcImg);
}

SR::SR()
{
    bgSubtractor = new BackgroundSubtractorMOG(20,10,0.5,0);
}

SR::~SR()
{

}

void SR::calculateSR(Mat &image, Mat &saliencyMap)
{
    int resImWidth  = 64,resImHeight = 64;
        Mat grayTemp, grayDown;
        //std::vector<Mat> mv;

        Size resizedImageSize( resImWidth, resImHeight );


       Mat realImage( resizedImageSize, CV_64F );
       Mat imaginaryImage( resizedImageSize, CV_64F );
       imaginaryImage.setTo( 0 );
       Mat combinedImage( resizedImageSize, CV_64FC2 );
       Mat imageDFT;
       Mat logAmplitude;
       Mat angle( resizedImageSize, CV_64F );
       Mat magnitude( resizedImageSize, CV_64F );
       Mat logAmplitude_blur, imageGR;

       if( image.channels() == 3 )
       {
         cvtColor( image, imageGR, COLOR_BGR2GRAY );
         resize( imageGR, grayDown, resizedImageSize, 0, 0, INTER_LINEAR );
       }
       else
       {
         resize( image, grayDown, resizedImageSize, 0, 0, INTER_LINEAR );
       }
        grayDown.convertTo( realImage, CV_64F );
        Mat mv[] = {realImage, imaginaryImage};

       //mv.push_back( realImage );
       //mv.push_back( imaginaryImage );

       merge( mv, 2,combinedImage );
       dft( combinedImage, imageDFT );
       split( imageDFT, mv );

       //-- Get magnitude and phase of frequency spectrum --//
       cartToPolar( mv[0], mv[1], magnitude, angle, 0 );
       log( magnitude, logAmplitude );
       //-- Blur log amplitude with averaging filter --//
       blur( logAmplitude, logAmplitude_blur, Size( 3, 3 ), Point( -1, -1 ), BORDER_DEFAULT );

       exp( logAmplitude - logAmplitude_blur, magnitude );//无须加入相位，因为之后的反变换就是论文中exp
       //exp( angle, magnitude );
       //magnitude = magnitude.mul( magnitude );
       //-- Back to cartesian frequency domain --//
       polarToCart( magnitude, angle, mv[0], mv[1], 0 );
       merge( mv,2, imageDFT );
       dft( imageDFT, combinedImage, DFT_INVERSE );
       split( combinedImage, mv );

       cartToPolar( mv[0], mv[1], magnitude, angle, 0);
       magnitude = magnitude.mul( magnitude );
       GaussianBlur( magnitude, magnitude, Size( 7, 7 ), 8, 0, BORDER_DEFAULT );
       magnitude = magnitude.mul( magnitude );

       double minVal, maxVal;
       minMaxLoc( magnitude, &minVal, &maxVal );

       magnitude = magnitude / maxVal;
       magnitude.convertTo( magnitude, CV_32F );

       resize( magnitude, saliencyMap, image.size(), 0, 0, INTER_LINEAR );
}


void SR::getSRsailencyMap(Mat &frame, Mat &sailencyMap, Mat &showBinImg)
{
    Mat proImg,mask;
    calculateSR(frame,proImg);
    proImg.convertTo(sailencyMap,CV_8UC1,255.0);
    (*bgSubtractor)(sailencyMap,mask,0.01);
    showBinImg = mask.clone();
    getObject(mask,frame);
}


myFT::myFT()
{
    bgSubtractor = new BackgroundSubtractorMOG(20,3,0.5,0);
}

myFT::~myFT()
{

}

void myFT::getSailencyMapFT(Mat &srcImg, Mat &sailencyMap)
{
    Mat labImg;
    //vector<Mat> mv;
    Mat mv[3];
    //GaussianBlur(srcImg,srcImg,Size(5,5),0);
    //imshow("高斯平滑后的图像",srcImg);
    cvtColor(srcImg,labImg,CV_BGR2Lab);
    //imshow("lab图像",labImg);
    split(labImg,mv);
    //imshow("LAB图像第一层",mv[0]);
    //imshow("LAB图像第二层",mv[1]);
    //imshow("LAB图像第三层",mv[2]);

    Scalar mean0,std0;
    meanStdDev(mv[0],mean0,std0);
    double mean0Val = mean0.val[0];
    double std0Val = std0.val[0];
    //cout<<std0.val[0]<<endl;

    Scalar mean1,std1;
    meanStdDev(mv[1],mean1,std1);
    double mean1Val = mean1.val[0];
    double std1Val = std1.val[0];
    //cout<<std1.val[0]<<endl;

    Scalar mean2,std2;
    meanStdDev(mv[2],mean2,std2);
    double mean2Val = mean2.val[0];
    double std2Val = std2.val[0];
    //cout<<std2.val[0]<<endl;

    Mat mv0;
    mv[0].convertTo(mv0,CV_32F);
    Mat mv0Img;
    pow(mv0-(Scalar::all(mean0Val)),2,mv0Img);
    Mat showMv0;
    normalize(mv0Img,showMv0,255.0);
    //imshow("显著图0",showMv0);

    Mat mv1;
    mv[1].convertTo(mv1,CV_32F);
    Mat mv1Img;
    pow(mv1-(Scalar::all(mean1Val)),2,mv1Img);
    Mat showMv1;
    normalize(mv1Img,showMv1,255.0);
    //imshow("显著图1",showMv1);

    Mat mv2;
    mv[2].convertTo(mv2,CV_32F);
    Mat mv2Img;
    pow(mv2-(Scalar::all(mean2Val)),2,mv2Img);
    Mat showMv2;
    normalize(mv2Img,showMv2,255.0);
    //imshow("显著图2",showMv2);

    Mat proSailencyMap = std0Val*showMv0+std1Val*showMv1+std2Val*showMv2;
    //sailencyMap.convertTo(showImg,CV_8U,255.0);
    normalize(proSailencyMap,sailencyMap,255.0);
}

void myFT::getFTmap(Mat &frame,Mat &sailencyMap,Mat &showBinImg,double learnRate)
{
    Mat proImg,mask;
    getSailencyMapFT(frame,proImg);
    proImg.convertTo(sailencyMap,CV_8U,255.0);
    //Mat grayImg;
    //cvtColor(frame,grayImg,CV_RGB2GRAY);
    //medianBlur(sailencyMap,sailencyMap,3);
    (*bgSubtractor)(sailencyMap,mask,learnRate);
    showBinImg = mask.clone();//纯粹为了演示用，其实这样复制图像会更加耗费时间
    medianBlur(showBinImg,showBinImg,3);
    //GaussianBlur(showBinImg,showBinImg,Size(5,5),0);

    getObject(mask,frame);
}

static int pairs[6][2] = {{2,5},{2,6},{3,6},{3,7},{4,7},{4,8}};
IttiModel::IttiModel()
{
    bgSubtractor = new BackgroundSubtractorMOG(20,10,0.5,0);
    pyrNum = 9;
    opNum = 6;
    STEP = 8;
    opSigama = 3;
    GABOR_R = 8;
    //pairs[6][2] = {{2,5},{2,6},{3,6},{3,7},{4,7},{4,8}};
}

IttiModel::~IttiModel()
{

}

void IttiModel::normalizeRange(Mat& image)
{
    double minval,maxval;
    minMaxLoc(image,&minval,&maxval);

    image-=minval;
    if(minval<maxval) //防止除零错
        image/=maxval-minval;
}

void IttiModel::trimPeaks(Mat& image,int step)
{
    //image.convertTo(image,CV_32FC1);
    const int w=image.cols;
    const int h=image.rows;

    const double M=1.0;
    normalizeRange(image);
    double m=0;
    for(int y=0;y<h-step;y+=step) //端は(h%step)だけ余る  步长为step依次递进搜索行与列
    for(int x=0;x<w-step;x+=step) //端は(w%step)だけ余る
    {
        Mat roi(image,Rect(x,y,step,step));//在step为边长的正方形窗口内求极大极小值
        double minval=0.0,maxval=0.0;
        minMaxLoc(roi,&minval,&maxval);
        m+=maxval;
    }
    m/=(w/step-(w%step?0:1))*(h/step-(h%step?0:1)); //ブロック数で割って平均を計算 计算局部极大值均值
    image*=((M-m)*(M-m));
    //image.convertTo(image,CV_8UC1);
}


//函数作用：生成图像高斯金字塔
//输入参数：原始图像、金字塔层数，金字塔vector容器
//返回值：无
void IttiModel::createPyrmaid(Mat& srcImg,int pyrNum,vector<Mat> &pyrList)
{
    //srcImg.convertTo(srcImg,CV_32FC1);
    Mat_<float> image=srcImg/255.0f;//将原有的图像转换为浮点型，便于后续的削尖峰运算，即金字塔全部为浮点型图像
    //Mat image = srcImg;
    Mat dstImg;

    pyrList.push_back(image);
    Mat tempImg = image;
    for(int i = 0;i < pyrNum-1;i++)
    {
        pyrDown(tempImg,dstImg);
        pyrList.push_back(dstImg);
        tempImg = dstImg;
    }
}

void IttiModel::getGrayPyrmaid(Mat& grayImg,int pyrNum,vector<Mat> &grayPyrMaid)
{
    createPyrmaid(grayImg,pyrNum,grayPyrMaid);
}



//函数作用：获取四种颜色颜色特征图
//输入参数：原始图像，四种颜色特征图vector容器
//返回值：无
void IttiModel::getColorFeatureMap(Mat& srcImg,vector<Mat> &colorFeatureMap)
{
    int rows = srcImg.rows;
    int cols = srcImg.cols;
    //int channels = srcImg.channels();
    //int colNum = cols*channels;
    Mat redMap = Mat::zeros(srcImg.size(),CV_8UC1);
    Mat greenMap = Mat::zeros(srcImg.size(),CV_8UC1);
    Mat blueMap = Mat::zeros(srcImg.size(),CV_8UC1);
    Mat yellowMap = Mat::zeros(srcImg.size(),CV_8UC1);
    for (int i = 0;i < rows;i++)
    {
        uchar *data = srcImg.ptr<uchar>(i);
        uchar *rdata = redMap.ptr<uchar>(i);
        uchar *bdata = blueMap.ptr<uchar>(i);
        uchar *gdata = greenMap.ptr<uchar>(i);
        uchar *ydata = yellowMap.ptr<uchar>(i);
        for (int j = 0;j < cols;j++)
        {
            int b = data[3*j];
            int g = data[3*j+1];
            int r = data[3*j+2];
            bdata[j] = saturate_cast<uchar>(b-(g+r)/2);
            rdata[j] = saturate_cast<uchar>(r-(g+b)/2);
            gdata[j] = saturate_cast<uchar>(g-(r+b)/2);
            ydata[j] = saturate_cast<uchar>((r+g)/2-abs(r-g)/2-b);
        }
    }
    /*
    imshow("r",redMap);
    imshow("g",greenMap);
    imshow("b",blueMap);
    imshow("y",yellowMap);
    */
    colorFeatureMap.push_back(redMap);
    colorFeatureMap.push_back(greenMap);
    colorFeatureMap.push_back(blueMap);
    colorFeatureMap.push_back(yellowMap);
}



//函数作用：获取亮度显著图
//输入参数：亮度金字塔，亮度特征图（要求与基准层相同尺度），相加基准层，归一化尺度
//返回值：无

void IttiModel::getGraySailencyMap(vector<Mat> &grayPyrMaid,Mat& ansImg,int opSigama)
{

    Mat subFeatureMap[6];
    Mat tempImg1,tempImg2;

    //中央周边差操作
    for(int i = 0;i < opNum;i++)
    {
        int c = pairs[i][0];
        int s = pairs[i][1];
        resize(grayPyrMaid[s],tempImg1,grayPyrMaid[c].size(),0,0,INTER_NEAREST);
        //absdiff(grayPyrMaid[c],tempImg1,subFeatureMap[i]);
        subFeatureMap[i] = abs(grayPyrMaid[c]-tempImg1);
    }
    //跨尺度相加操作
    for(int i = 0;i < opNum;i++)
    {
        trimPeaks(subFeatureMap[i],STEP);
        resize(subFeatureMap[i],tempImg2,grayPyrMaid[opSigama].size(),0,0,INTER_NEAREST);
        ansImg += tempImg2;
    }
}


//函数作用：获取色彩显著图
//输入参数：四种色彩特征图，色彩显著图矩阵，相加基准层，归一化尺度
//返回值：无
void IttiModel::getColorSailencyMap(vector<Mat> &colorFeatureMap,Mat& ansImg,int opSigama)
{
    vector<Mat> bluePyr;
    vector<Mat> redPyr;
    vector<Mat> greenPyr;
    vector<Mat> yellowPyr;
    createPyrmaid(colorFeatureMap[0],9,redPyr);
    createPyrmaid(colorFeatureMap[1],9,greenPyr);
    createPyrmaid(colorFeatureMap[2],9,bluePyr);
    createPyrmaid(colorFeatureMap[3],9,yellowPyr);

    Mat tempImg1,tempImg2,tempImg3;
    Mat RGImg[6];
    Mat BYImg[6];

    //中央周边差操作
    for(int i = 0;i < 6;i++)
    {
        int c = pairs[i][0];
        int s = pairs[i][1];
        subtract(redPyr[c],greenPyr[c],tempImg1);
        subtract(greenPyr[s],redPyr[s],tempImg2);
        resize(tempImg2,tempImg3,tempImg1.size(),0,0,INTER_NEAREST);
        absdiff(tempImg1,tempImg3,RGImg[i]);

        subtract(bluePyr[c],yellowPyr[c],tempImg1);
        subtract(yellowPyr[s],bluePyr[s],tempImg2);
        resize(tempImg2,tempImg3,tempImg1.size(),0,0,INTER_NEAREST);
        absdiff(tempImg1,tempImg3,BYImg[i]);
    }

    Mat tempImg4,tempImg5;
    Size opSigamaSize = RGImg[opSigama].size();

    //跨尺度相加操作

    for(int i = 0;i < 6;i++)
    {
        trimPeaks(RGImg[i],STEP);
        trimPeaks(BYImg[i],STEP);
        add(RGImg[i],BYImg[i],tempImg4);
        resize(tempImg4,tempImg5,opSigamaSize,0,0,0);
        add(ansImg,tempImg5,ansImg);
    }

}


//Mat IttiModel::operateCenterSurround(const Mat& center,const Mat& surround)
//{
//    Mat csmap(center.size(),center.type());
//    resize(surround,csmap,csmap.size()); //surround画像をcenter画像と同サイズに拡大
//    csmap=abs(center-csmap);
//    return csmap;
//}


//vector<Mat> IttiModel::buildCenterSurroundPyramid(const vector<Mat>& pyramid)
//{
//    //surround=center+delta, center={2,3,4}, delta={3,4} 計6枚
//    vector<Mat> cspyr(6);
//    cspyr[0]=operateCenterSurround(pyramid[2],pyramid[5]);
//    cspyr[1]=operateCenterSurround(pyramid[2],pyramid[6]);
//    cspyr[2]=operateCenterSurround(pyramid[3],pyramid[6]);
//    cspyr[3]=operateCenterSurround(pyramid[3],pyramid[7]);
//    cspyr[4]=operateCenterSurround(pyramid[4],pyramid[7]);
//    cspyr[5]=operateCenterSurround(pyramid[4],pyramid[8]);
//    return cspyr;
//}
//void IttiModel::getOrientionSailencyMap(Mat& image0,Mat& ansImg)
//{
//    const Mat_<Vec3f> image=image0/255.0f;

//    const Size ksize=Size(GABOR_R+1+GABOR_R,GABOR_R+1+GABOR_R);
//    const double sigma=GABOR_R/CV_PI; //±πσまでサポートするように調整
//    const double lambda=GABOR_R+1; //片側を1周期に調整
//    const double deg45=CV_PI/4.0;
//    Mat gabor000=getGaborKernel(ksize,sigma,deg45*0,lambda,1.0,0.0,CV_32F);
//    Mat gabor045=getGaborKernel(ksize,sigma,deg45*1,lambda,1.0,0.0,CV_32F);
//    Mat gabor090=getGaborKernel(ksize,sigma,deg45*2,lambda,1.0,0.0,CV_32F);
//    Mat gabor135=getGaborKernel(ksize,sigma,deg45*3,lambda,1.0,0.0,CV_32F);

//    const int NUM_SCALES=pyrNum;
//    vector<Mat> pyramid000(NUM_SCALES); //方向  0°ピラミッド
//    vector<Mat> pyramid045(NUM_SCALES); //方向 45°ピラミッド
//    vector<Mat> pyramid090(NUM_SCALES); //方向 90°ピラミッド
//    vector<Mat> pyramid135(NUM_SCALES); //方向135°ピラミッド

//    Mat scaled=image;
//    Mat imageI;
//    for(int i = 0;i < pyrNum;i++)
//    {
//        cvtColor(scaled,imageI,CV_RGB2GRAY);
//        filter2D(imageI,pyramid000[i],-1,gabor000);
//        filter2D(imageI,pyramid045[i],-1,gabor045);
//        filter2D(imageI,pyramid090[i],-1,gabor090);
//        filter2D(imageI,pyramid135[i],-1,gabor135);
//        pyrDown(scaled,scaled);
//    }

//    vector<Mat> cspyr000=buildCenterSurroundPyramid(pyramid000);
//    vector<Mat> cspyr045=buildCenterSurroundPyramid(pyramid045);
//    vector<Mat> cspyr090=buildCenterSurroundPyramid(pyramid090);
//    vector<Mat> cspyr135=buildCenterSurroundPyramid(pyramid135);
//    Mat_<float> temp(image.size());
//    Mat_<float> consp000(image.size(),0.0f);
//    Mat_<float> consp045(image.size(),0.0f);
//    Mat_<float> consp090(image.size(),0.0f);
//    Mat_<float> consp135(image.size(),0.0f);
//    for(int t=0;t<int(cspyr000.size());++t) //CSピラミッドの各層について
//    {

//        //方向特徴マップへの加算
//        trimPeaks(cspyr000[t],STEP); resize(cspyr000[t],temp,image.size()); consp000+=temp;
//        trimPeaks(cspyr045[t],STEP); resize(cspyr045[t],temp,image.size()); consp045+=temp;
//        trimPeaks(cspyr090[t],STEP); resize(cspyr090[t],temp,image.size()); consp090+=temp;
//        trimPeaks(cspyr135[t],STEP); resize(cspyr135[t],temp,image.size()); consp135+=temp;
//    }
//    trimPeaks(consp000,STEP);
//    trimPeaks(consp045,STEP);
//    trimPeaks(consp090,STEP);
//    trimPeaks(consp135,STEP);
//    ansImg = consp000+consp045+consp090+consp135;


//}

void IttiModel::getSailencyMap(Mat &srcImg,Mat &sailencyMap)
{
    vector<Mat> grayPyrMaid;
    Mat grayImg;
    cvtColor(srcImg,grayImg,CV_BGR2GRAY);
    getGrayPyrmaid(grayImg,pyrNum,grayPyrMaid);
    Mat graySailencyMap = Mat::zeros(grayPyrMaid[opSigama].size(),CV_32FC1);
    getGraySailencyMap(grayPyrMaid,graySailencyMap,opSigama);

    vector<Mat> colorFeatureMap;
    getColorFeatureMap(srcImg,colorFeatureMap);
    Mat colorSailencyMap = Mat::zeros(grayPyrMaid[opSigama].size(),CV_32FC1);
    getColorSailencyMap(colorFeatureMap,colorSailencyMap,opSigama);
    /*
    Mat_<float> orientSailencyMap;
    getOrientionSailencyMap(srcImg,orientSailencyMap);
    */

    Mat rawSailencyMap = (graySailencyMap+colorSailencyMap)/2;
    resize(rawSailencyMap,sailencyMap,Size(320,240));

}


void IttiModel::getSailencyMapItti(Mat &frame,Mat &sailnecyMap,Mat &showBinImg)
{
    Mat proImg,mask;
    getSailencyMap(frame,proImg);
    proImg.convertTo(sailnecyMap,CV_8UC1,255.0);
    (*bgSubtractor)(sailnecyMap,mask,0.01);
    showBinImg = mask.clone();//纯粹为了演示用，其实这样复制图像会更加耗费时间
    getObject(mask,frame);
}

LC::LC()
{
    bgSubtractor = new BackgroundSubtractorMOG(20,10,0.5,0);
}

LC::~LC()
{

}
void LC::LCOperation(Mat &srcImg,Mat &sailencyMap)
{
    Mat grayImg;

    cvtColor(srcImg,grayImg,CV_RGB2GRAY);
    //imshow("grayImg",grayImg);

        //统计直方图
    int hist[256] = {0};
    int nr=grayImg.rows;
    int nl=grayImg.cols*grayImg.channels();
    for(int k=0;k<nr;k++)
    {
        const uchar* inData=grayImg.ptr<uchar>(k);
        for(int i=0;i<nl;i++)
        {
            hist[inData[i]]++;
         }
    }

     //统计像素距离
    int Dist[256] = {0};
    for (int i = 0;i < 256;i++)
    {
            //cout<<hist[i]<<endl;
        int val = 0;
        for (int j = 0;j < 256;j++)
        {
            val += abs(i-j)*hist[i];
        }
        Dist[i] = val;
            //cout<<val<<endl;
    }

    for(int i = 0;i < sailencyMap.rows;i++)
    {
        for(int j = 0;j < sailencyMap.cols;j++)
        {
            sailencyMap.at<float>(i,j) = Dist[grayImg.at<uchar>(i,j)];
        }
    }
}
void LC::getLCsailencyMap(Mat &frame,Mat &sailencyMap,Mat &showBinImg)
{

    Mat proImg = Mat::zeros(frame.size(),CV_32F);//在内部建立此图会拖慢速度，正在想办法解决
    Mat mask;
    LCOperation(frame,proImg);
    proImg.convertTo(sailencyMap,CV_8UC1,255.0);
    medianBlur(sailencyMap,sailencyMap,3);
    (*bgSubtractor)(sailencyMap,mask,0.01);
    showBinImg = mask.clone();
    getObject(mask,frame);
}

originalGMM::originalGMM()
{
     bgSubtractor = new BackgroundSubtractorMOG(20,10,0.5,0);
}

originalGMM::~originalGMM()
{

}

void originalGMM::getGMMMap(Mat &frame, Mat &showBinImg)
{
    Mat mask;
    //BackgroundSubtractorMOG bgSubtractor1(20,10,0.5,false);
    //bgSubtractor1(frame,mask,0.01);
    //imshow("mask",mask);
    (*bgSubtractor)(frame,mask,0.01);
    showBinImg = mask.clone();
    getObject(mask,frame);
}

void originalGMM::getGrayGMMMap(Mat &frame, Mat &showBinImg)
{
    Mat grayImg,mask;
    cvtColor(frame,grayImg,CV_RGB2GRAY);
    (*bgSubtractor)(grayImg,mask,0.01);
    showBinImg = mask.clone();
    getObject(mask,frame);
}





