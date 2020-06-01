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
    
    unsigned choice;
    while(1)
    {
        cout << endl << "Choose the Effect to apply" << endl;
        cout << "1. Plot Histogram" << endl << "2. Lomography Effect" << endl << "3. Catoonize Effect" << endl << "4. Exit" << endl << endl;
        cout << "Enter the choice: - ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                PlotHistogram(image);
                break;
            case 2:
                LomographyEffect(image);
                break;
            case 3:
                CartoonizeEffect(image);
                break;
            case 4:
                return 0;
            default:
                cout << "Enter the correct choose" << endl;
                break;
        }
    }    
    return 0;
}
