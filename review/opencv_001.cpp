/* ************************************************************************
> File Name:     opencv_001.cpp
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 25 Jan 2023 06:29:52 PM CST
> Description:   
 ************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {

    Mat src = imread("./test.png", IMREAD_GRAYSCALE);

    if (src.empty()) {
    
        printf("could not load image...\n");
        return -1;
    }
    nameWindow("input", CV_WINDOW_AUTOSIZE);
    imshow("input", src);

    waitKey(0);

    return 0;
}
