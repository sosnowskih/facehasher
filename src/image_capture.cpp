//image_capture.cpp
//CS 201
//Henryk Sosnowski and Bryan Beus
//October 12, 2019
 //Captures an image from a web camera and saves the image to a local folder


#include <iostream>
#include <opencv2/opencv.hpp>
#include "facehasher.hpp"


//This function opens a new window with the computer's default camera settings and allows the user to save the current frame as a jpg.
//It returns true if an image was saved or false if it failed to open the camera.
void image_capture(bool & cancontinue)
{
	//Attempt to open the camera using the computer's default camera settings
	cv::VideoCapture cap(0);

	//Exits the function if there is an issue accessing the camera
	//Changes the referenced bool value to signal the program to stop
	if (!cap.isOpened())
	{
		std::cout << "Error: Cannot open camera.";
		cancontinue = false;
		return;
	}

	//The window name visible to the user
	std::string windowName = "Press any key to take a picture.";

	//This Mat object will story the current frame
	cv::Mat frame;

	//Opens a currently empty window with the passed name
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	while (true)
	{
		//Opens a camera object with live feed visible to the user.  
		//The name must be the same as the previous window for them to combine for complete functionality
		cap >> frame;
		cv::imshow(windowName, frame);

		//The program waits until a key press is detected
		char key = cv::waitKey(30);

		//Any key press will save the current frame to the source directory as "image.jpg"
		if (key > 0)
		{
			cv::imwrite("image.jpg", frame);
			std::cout << "Image captured." << std::endl;
			break;
		}
	}

	//The window is destroyed upon completion.  Necessary for UI integration.
	cv::destroyWindow(windowName);

	return;
}
