//
//  2_HistogramAndEffect.hpp
//  OpenCV_Cpp
//
//  Created by Ashwani on 01/06/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//
#include <iostream>
#include <vector>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

#ifndef __HistogramAndEffect_h
#define __HistogramAndEffect_h



void PlotHistogram(Mat data)
{
    Mat image = data;
    Mat equalizeHistImage, b_hist, g_hist, r_hist;
    Mat grayImage;
    
     /// Convert to grayscale
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    if(grayImage.empty())
    {
        cout << "unable to convert to gray image" << endl;
        return;
    }
    
    /// Separate the image in  3 Places (R, G, B)
    vector<Mat> rgbPlane;
    split(image, rgbPlane);
    
    /// Establish the number of bins
    int histSize = 256;
    
    /// Set the ranges ( for R,G,B)
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    
    bool uniform = true;
    bool accumulate = false;
    
    /// Compute the histograms:
    calcHist(&rgbPlane[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgbPlane[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&rgbPlane[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Draw the histogram, We going to draw lines for each channel
    int width= 512;
    int height= 300;
    
    // Create image with gray base
    Mat histImage(height, width, CV_8UC3, Scalar( 0,0,0) );
    
    // Normalize the histograms to height of image
    normalize(r_hist, r_hist, 0, height, NORM_MINMAX );
    normalize(g_hist, g_hist, 0, height, NORM_MINMAX );
    normalize(b_hist, b_hist, 0, height, NORM_MINMAX );
    
    
    
    int bin_w = cvRound( (double) width/histSize );
    
    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), height - cvRound(b_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), height - cvRound(b_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), height - cvRound(g_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), height - cvRound(g_hist.at<float>(i)) ),
                         Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), height - cvRound(r_hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), height - cvRound(r_hist.at<float>(i)) ),
                         Scalar( 0, 0, 255), 2, 8, 0  );

    }
    
    /// Apply Histogram Equalization
    equalizeHist(grayImage, equalizeHistImage);
    
    //Create and move windows
    namedWindow("Histogram", WINDOW_AUTOSIZE);
    namedWindow("Histogram Equalization", WINDOW_AUTOSIZE);
    moveWindow("Histogram", 10, 10);
    moveWindow("Histogram Equalization", 540, 10);
    
    imshow("Histogram", histImage);
    imshow("Histogram Equalization", equalizeHistImage);
    
    waitKey(0);
    
    destroyAllWindows();
    return;
}


void LomographyEffect(Mat data)
{
    Mat image = (data);
    Mat LomographyImage;
    
    const double E = exp(1.0);
    
    /// Create Lookup table for color curve effect
    Mat LookUpTable(1, 256, CV_8UC1);
    for (int i=0; i<256; i++)
    {
        float x= (float)i/256.0;
        LookUpTable.at<uchar>(i)= cvRound( 256 * (1/(1 + pow(E, -((x-0.5)/0.1)) )) );
    }
    
    /// Split the image channels and apply curve transform only to red channel
    vector<Mat> bgr;
    split(image, bgr);
    LUT(bgr[2], LookUpTable, bgr[2]);
    
    /// merge result
    merge(bgr, LomographyImage);
    
    /// Create image for halo dark
    Mat halo( image.rows, image.cols, CV_32FC3, Scalar(0.3,0.3,0.3) );
    
    /// Create circle
    circle(halo, Point(image.cols/2, image.rows/2), image.cols/3, Scalar(1,1,1), -1);
    blur(halo, halo, Size(image.cols/3, image.cols/3));
    
    /// Convert the result to float to allow multiply by 1 factor
    Mat resultf;
    LomographyImage.convertTo(resultf, CV_32FC3);
    
    // Multiply our result with halo
    multiply(resultf, halo, resultf);
    
    // convert to 8 bits
    resultf.convertTo(LomographyImage, CV_8UC3);
    
    // show result
    imshow("Lomograpy", LomographyImage);
    waitKey(0);
    
    // Release mat memory
    halo.release();
    resultf.release();
    LookUpTable.release();
    bgr[0].release();
    bgr[1].release();
    bgr[2].release();
    
    destroyAllWindows();
    
    return;
}

void CartoonizeEffect(Mat data)
{
    Mat image = data;
    
    /* EDGES */
    /// Apply median filter to remove possible noise
    Mat imgMedian;
    medianBlur(image, imgMedian, 7);
    
    /// Detect edges with canny
    Mat imgCanny;
    Canny(imgMedian, imgCanny, 50, 150);
    
    /// Dilate the edges
    Mat kernel= getStructuringElement(MORPH_RECT, Size(2,2));
    dilate(imgCanny, imgCanny, kernel);
    
    /// Scale edges values to 1 and invert values
    imgCanny= imgCanny/255;
    imgCanny= 1-imgCanny;
    
    /// Use float values to allow multiply between 0 and 1
    Mat imgCannyf;
    imgCanny.convertTo(imgCannyf, CV_32FC3);
    
    /// Blur the edgest to do smooth effect
    blur(imgCannyf, imgCannyf, Size(5,5));
    
    /* COLOR **/
    /// Apply bilateral filter to homogenizes color
    Mat imgBF;
    bilateralFilter(image, imgBF, 9, 150.0, 150.0);
    
    /// Truncate colors
    Mat result= imgBF/25;
    result= result*25;

    /* MERGES COLOR + EDGES */
    /// Create a 3 channles for edges
    Mat imgCanny3c;
    Mat cannyChannels[]={ imgCannyf, imgCannyf, imgCannyf};
    merge(cannyChannels, 3, imgCanny3c);
    
    // Convert color result to float
    Mat resultf;
    result.convertTo(resultf, CV_32FC3);

    // Multiply color and edges matrices
    multiply(resultf, imgCanny3c, resultf);

    // convert to 8 bits color
    resultf.convertTo(result, CV_8UC3);

    // Show image
    imshow("Result", result);
    waitKey(0);
    
    destroyAllWindows();
}
#endif /* __HistogramAndEffect_h */
