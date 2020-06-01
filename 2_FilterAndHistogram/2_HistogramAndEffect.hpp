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



void PlotHistogram(void *data)
{
    Mat *image = static_cast<Mat *>(data);
    Mat equalizeHistImage, b_hist, g_hist, r_hist;
    Mat grayImage;
    
     /// Convert to grayscale
    cvtColor(*image, grayImage, COLOR_BGR2GRAY);
    if(grayImage.empty())
    {
        cout << "unable to convert to gray image" << endl;
        return;
    }
    
    /// Separate the image in  3 Places (R, G, B)
    vector<Mat> rgbPlane;
    split(*image, rgbPlane);
    
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
    return;
}


#endif /* __HistogramAndEffect_h */
