//
//  2_HistogramAndEffect.cpp
//  2_FilterAndHistogram
//
//  Created by Ashwani on 01/06/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//

/*
 About : - Code cover the following topic
 1) Calculating and drawing a histogram
 2) Histogram equalization
 3) The lomography camera effect
 4) The cartoonize effect
 */


#include "2_HistogramAndEffect.hpp"



int main()
{
    Mat image = imread("../images/lena_color.bmp");
    if(image.empty())
    {
        cout << "Provide the right path to file" << endl;
        return -1;
    }
    
    PlotHistogram(&image);
    
    return 0;
}
