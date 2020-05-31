//
//  2_ControlMouseEvent.cpp
//  1_GUI
//
//  Created by Ashwani on 31/05/20.
//  Copyright © 2020 Ashwani. All rights reserved.
//

/*
 About: - going to paint green circles in an image, using mouse events, and blur the image with the slider.
 */

#include <iostream>
#include <sstream>

using namespace std;

//opencv Library
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

// Create a variable to save the position value in track
int blurAmount=15;

// Trackbar call back function
static void onChange(int pos, void* userInput);

//Mouse callback
static void onMouse( int event, int x, int y, int, void* userInput );

int main( int argc, const char** argv )
{
    // Read images
    Mat lena= imread("./images/lena_color.bmp");
    
    //Check for image
    if(!lena.data)
    {
        cout << endl << "Image file not found. Check the path!!" << endl << endl;
        return -1;
    }
    
    // Create windows
    namedWindow("Lena");
    
    // create a trackbark
    createTrackbar("Lena", "Lena", &blurAmount, 30, onChange, &lena);
    
    setMouseCallback("Lena", onMouse, &lena);

    // Call to onChange to init
    onChange(blurAmount, &lena);
        
    // wait app for a key to exit
    waitKey(0);
    
    // Destroy the windows
    destroyWindow("Lena");
    
    return 0;
}

// Trackbar call back function
static void onChange(int pos, void* userInput)
{
    if(pos <= 0)
        return;
    // Aux variable for result
    Mat imgBlur;

    // Get the pointer input image
    Mat* img= (Mat*)userInput;

    // Apply a blur filter
    blur(*img, imgBlur, Size(pos, pos));
    
    // Show the result
    imshow("Lena", imgBlur);
}

//Mouse callback
static void onMouse( int event, int x, int y, int, void* userInput )
{
    //any event other than EVENT_LBUTTONDOWN is discarded.
    if( event != EVENT_LBUTTONDOWN )
            return;

    // Get the pointer input image
    Mat* img= (Mat*)userInput;
    
    // Draw circle
    circle(*img, Point(x, y), 10, Scalar(0,255,0), 3);

    // Call on change to get blurred image
    onChange(blurAmount, img);

}
