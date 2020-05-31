//
//  main.cpp
//  1_Basic
//
//  Created by Ashwani on 31/05/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//


//#include <iostream>
//#include <string>
//#include <sstream>
//
//using namespace std;

//opencv Library
#include "opencv2/opencv.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, const char** argv)
{
  
    // create our writter
    FileStorage fs("test.yml", FileStorage::WRITE);
    
    // Save an int
    int fps= 5;
    fs << "fps" << fps;
    
    // Create some mat sample
    Mat m1= Mat::eye(2,3, CV_32F);
    Mat m2= Mat::ones(3,2, CV_32F);
    Mat result= (m1+1).mul(m1+3);
    
    // write the result
    fs << "Result" << result;
    // release the file
    fs.release();
    
    FileStorage fs2("test.yml", FileStorage::READ);
    
    Mat r;
    fs2["Result"] >> r;
    std::cout << r << std::endl;
    
    fs2.release();
    
    return 0;
}
