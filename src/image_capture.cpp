/**
 * image_capture.cpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * Captures an image from a web camera and saves the image to a local folder
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include "facehasher.hpp"


//This function opens a new window with the computer's default camera settings and allows the user to save the current frame as a jpg.
//It returns true if an image was saved or false if it failed to open the camera or was closed before a picture was taken.
bool image_capture()
{
	char key;
	cv::VideoCapture cap(0);

	//Check for any failure in opening the camera
	if (!cap.isOpened())
	{
		std::cout << "Error: Cannot open camera.";
		return false;
	}

	std::cout << "Press 'c' to capture an image.  Press 'q' to quit." << std::endl;

	//Open a new window displaying the current camera feed
	cv::Mat frame;
	cv::namedWindow("Capture", cv::WINDOW_AUTOSIZE);

	//Upon user input, either saves the current frame as "image.jpg" to the root directory or exits the function
	bool captured = false;
	while (true)
	{
		cap >> frame;
		cv::imshow("Capture", frame);

		key = cv::waitKey(30);

		if (key == 'c')
		{
			cv::imwrite("image.jpg", frame);
			std::cout << "Image captured." << std::endl;
			captured = true;
		}
		if (key == 'q')
		{
			break;
		}
	}

	return captured;
}