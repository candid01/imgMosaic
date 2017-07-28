/*
 * Features.hpp
 *  Created on: Jul 03, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef HEADERS_FEATURES_HPP_
#define HEADERS_FEATURES_HPP_

#include "opencv2/xfeatures2d.hpp"												// import the library that has SURF implementation
#include <opencv2/opencv.hpp>													// import the library to convert image color

using namespace cv::xfeatures2d;

class Features
{
public:
	virtual ~Features(){};
	// Getters
	cv::Mat 				  getDescriptors();									// return descriptors attribute
	std::vector<cv::KeyPoint> getKeypoints();									// return keipoints attributes

	// Others Methods
	void computeKeypointsAndDescriptors_SURF(int minHessian, cv::Mat image);	// compute the keypoints and descriptors using the algorithm SURF
private:
	cv::Mat 				  descriptors;										// descriptor used in matching features algorithm
	std::vector<cv::KeyPoint> keypoints;										// keypoints extracted from image
};
#endif /* HEADERS_FEATURES_HPP_ */
