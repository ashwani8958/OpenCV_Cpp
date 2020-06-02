//
//  3_HistogramOfGrayImage.cpp
//  2_FilterAndHistogram
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

void show_histogram(std::string const& name, cv::Mat1b const& image)
{
    // Set histogram bins count
    int bins = 256;
    int histSize[] = {bins};
    // Set ranges for histogram bins
    float lranges[] = {0, 256};
    const float* ranges[] = {lranges};
    // create matrix for histogram
    cv::Mat hist;
    int channels[] = {0};

    // create matrix for histogram visualization
    int const hist_height = 256;
    cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

    double max_val=0;
    minMaxLoc(hist, 0, &max_val);

    // visualize each bin
    for(int b = 0; b < bins; b++)
    {
        float const binVal = hist.at<float>(b);
        int   const height = cvRound(binVal*hist_height/max_val);
        cv::line
            ( hist_image
            , cv::Point(b, hist_height-height), cv::Point(b, hist_height)
            , cv::Scalar::all(255)
            );
    }
    cv::imshow(name, hist_image);
}

int main (int argc, const char* argv[])
{
    // here you can use cv::IMREAD_GRAYSCALE to load grayscale image, see image2
    cv::Mat3b const image1 = cv::imread("../images/lena_color.bmp", cv::IMREAD_COLOR);
    cv::Mat1b image1_gray;
    cv::cvtColor(image1, image1_gray, cv::COLOR_BGR2GRAY);
    cv::imshow("image1", image1_gray);
    show_histogram("image1 hist", image1_gray);
    
    cv::Mat1b const image2 = cv::imread("../images/lena_color.bmp", cv::IMREAD_GRAYSCALE);
    cv::imshow("image2", image2);
    show_histogram("image2 hist", image2);

    cv::waitKey();
    return 0;
}
