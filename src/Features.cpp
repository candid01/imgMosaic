/*
 * Features.cpp
 *  Created on: Jul 03, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../headers/Features.hpp"
#include <iostream>

// Getters
std::vector<cv::KeyPoint> Features::getKeypoints()
{
	return this->keypoints;
}

cv::Mat Features::getDescriptors(){
	return this->descriptors;
}

// Others Methods
void Features::computeKeypointsAndDescriptors_SURF(int minHessian, cv::Mat image)
{
	cv::Mat grayscale;
	cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);

	cv::Ptr<SURF> SURF_detector = SURF::create();

	SURF_detector->setHessianThreshold(minHessian);
	SURF_detector->detectAndCompute(grayscale, cv::Mat(), this->keypoints, this->descriptors);

}
