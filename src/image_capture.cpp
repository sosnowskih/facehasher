/**
 * image_capture.cpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * Captures an image from a web camera and saves the image to a local folder
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "facehasher.hpp"

bool image_capture()
{
	char key;
	cv::VideoCapture cap(0);

	if (!cap.isOpened())
	{
		std::cout << "Error: Cannot open camera.";
		return false;
	}

	std::cout << "Press 'c' to capture an image.  Press 'q' to quit." << std::endl;

	cv::Mat frame;
	cv::namedWindow("Capture", cv::WINDOW_AUTOSIZE);
	while (true)
	{
		cap >> frame;
		cv::imshow("Capture", frame);

		key = cv::waitKey(30);

		if (key == 'c')
		{
			cv::imwrite("image.jpg", frame);
			std::cout << "Image captured." << std::endl;
		}
		if (key == 'q')
		{
			break;
		}
	}

	return true;
}