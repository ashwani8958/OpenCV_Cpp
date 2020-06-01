//
//  1_BasicFilter.cpp
//  2_FilterAndHistogram
//
//  Created by Ashwani on 01/06/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//

/*
 About code :- Apply the two basic filter on the image.
 */

#include <iostream>

//Open CV Include
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[])
{
    Mat lena = imread("../images/lena_color.bmp");
    Mat BlurFilterResult, SobelFilterResult;
    
    if(!lena.data)
    {
        cout<<"check the path of the image file"<<endl;
        return -1;
    }
   
    
    //Apply blur filter
    blur(lena, BlurFilterResult, Size(5,5));
    
    //Apply Sobel Filter
    //we use the x and y derivate simultaneously, overwriting the input, to generate the x and y derivates simultaneously, adding 1 in the fourth and fifth parameters
    Sobel(lena, SobelFilterResult, CV_8U, 1, 1);
    
    
    //Create the window and Move
    namedWindow("Blur Filter Applied", WINDOW_AUTOSIZE);
    namedWindow("Sobel Filter Applied", WINDOW_AUTOSIZE);
    moveWindow("Blur Filter Applied", 10, 10);
    moveWindow("Sobel Filter Applied", 550, 10);
    
    //Show blur filter image
    imshow("Blur Filter Applied", BlurFilterResult);
    
    //Show Sobel filter image
    imshow("Sobel Filter Applied", SobelFilterResult);
    
    waitKey(0);
    
    return 0;
}
