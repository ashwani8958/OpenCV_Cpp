//
//  ImageImport.cpp
//  OpenCV_Cpp
//
//  Created by Ashwani on 30/05/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//opencv Library
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, const char** argv)
{
  
    //Open the image
    Mat color = imread("./images/lena_color.bmp");

    if(!color.data)
    {
        cout << "Enable to open the image! Check the Path or check image is available for operation" << endl;
        return -1;
    }

    //Convert the image to gray scale
    Mat gray;
//    cvtColor(color, gray, COLOR_BGR2GRAY);
    gray = imread("./images/lena_color.bmp", IMREAD_GRAYSCALE);

    //save grayscale image version
    imwrite("./images/lena_gray.bmp", gray);

    //Print value of some function with opencv function
    int myRow = color.cols - 1;
    int myCol = color.rows - 1;
    Vec3b pixel = color.at<Vec3b>(myRow, myCol);
    cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;


    //namedWindow("Gray Image", WINDOW_AUTOSIZE);
    imshow("Lena Color", color);
    imshow("Lena Gray", gray);
    waitKey(0);

    //release the memory
    color.release();
    gray.release();

    return 0;
}
