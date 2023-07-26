#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture fan("test_blue.mp4");
    if (!fan.isOpened())
        return -1;

    Mat img;
    Mat src;
    Mat dst;
    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(13, 13));
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(9, 9));

    vector<vector<Point>> contours; //轮廓点集
    vector<Point> conPoly; //多边形逼近结果，与轮廓一一对应
    vector<Point> hull; //凹包
    vector<Point> mergedHull; //合成凹包(整体)

    while (1)
    {
        fan >> img;
        if (img.empty())
            break;

        //压缩图片：
        resize(img, img, Size(640, 480), INTER_LINEAR);

        //通道分离：
        vector<Mat>channels;
        split(img, channels);
        src = channels[0];

        //去噪：
        threshold(src, dst, 70, 255, THRESH_BINARY);
        medianBlur(dst, dst, 7);
        dilate(dst, dst, kernel1);
        erode(dst, dst, kernel2);
        imshow("dst", dst);

        //圆检测：
        findContours(dst, contours, RETR_CCOMP, CHAIN_APPROX_TC89_KCOS); 
        RotatedRect Ell; //扇叶拟合椭圆
        Point2f center; //用来储存扇叶中点及整体中点
        Point2f ell[4]; //扇叶4顶点
        float radius; //整体外接圆半径
        for (auto it = contours.begin(); it != contours.end(); ++it)
        {
            double peri = arcLength(*it, true); //周长
            approxPolyDP(*it, conPoly, 0.046 * peri, true); //多边形近似

            //通过轮廓数量判断圆：
            if (conPoly.size() >= 5)
            {
                //找出拟合椭圆并返回四顶点和中心点：
                Ell = fitEllipse(*it);
                center = Ell.center;
                Ell.points(ell);

                //绘制：
                circle(img, center, 3, Scalar(0, 255, 120), -1);
                for (int p = 0; p < 4; p++)
                    circle(img, ell[p], 3, Scalar(0, 255, 120), -1);
            }

            //通过合成凹包(整体)作最小外接圆找中心点
            convexHull(*it, hull);
            mergedHull.insert(mergedHull.end(), hull.begin(), hull.end());
            minEnclosingCircle(mergedHull, center, radius);
            circle(img, center, 3, Scalar(0, 255, 120), -1);
        }
        imshow("img", img);
        waitKey(1);
    }
    return 0;
}
