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

void image_capture()

{
	char key;
	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cout << "Error: Cannot open camera.";
		return;
	}

	std::string windowName = "Press any key to take a picture.";

	cv::Mat frame;
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	while (true)
	{
		cap >> frame;
		cv::imshow(windowName, frame);

		key = cv::waitKey(30);

		if (key > 0)
		{
			cv::imwrite("image.jpg", frame);

			break;
		}
		if (key == 'q')
		{
			break;
		}
	}

	cv::destroyWindow(windowName);

	return;

}
