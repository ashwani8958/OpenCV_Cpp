//
//  main.cpp
//  1_GUI
//
//  Created by Ashwani on 31/05/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//opencv Library
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, char **argv)
{
    //Read images
    Mat lena = imread("../images/lena_color.bmp");
    Mat profile = imread("../images/profile.jpg");
    
    //Check for image
    if(!lena.data)
    {
        cout << endl << "Image file not found. Check the path!!" << endl << endl;
        return -1;
    }
    if(!profile.data)
    {
        cout << endl << "Image file not found. Check the path!!" << endl << endl;
    }
    
    
    //Create the window
    namedWindow("Lena", WINDOW_NORMAL);                 //  WINDOW_NORMAL flag allows the user to resize the window
    namedWindow("Profile", WINDOW_AUTOSIZE);            // WINDOW_AUTOSIZE Flag the window size is automatically adjusted to fit the display image and it is not possible to resize the window

    
    //Move Window
    moveWindow("Lena", 10, 10);
    moveWindow("Profile", 520, 10);
    
    //Show
    imshow("Lena", lena);
    imshow("Profile", profile);
    
    //Resize window, only non autosize
    resizeWindow("Lena", 512, 512);
    
    //Wait any key to press
    waitKey(0);
    
    //destroy the window
    destroyWindow("Lena");
    destroyWindow("Profile");
    
    //Create 10 windows
    for(int i = 1; i <= 10; i++)
    {
        ostringstream ss;
        ss << "Profile" << i;
        namedWindow(ss.str());
        moveWindow(ss.str(), 20*i, 20*i);
        imshow(ss.str(), profile);
    }
    
    waitKey(0);
    destroyAllWindows();
    
    return 0;
}
