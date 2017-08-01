/*
 * Triangulation.hpp
 *  Created on: Jul 05, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef INCLUDE_TRIANGULATION_HPP_
#define INCLUDE_TRIANGULATION_HPP_

//#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include "opencv2/sfm.hpp"
#include <stdio.h>

using cv::Mat;
using cv::Point2f;
using namespace cv::sfm;
using std::vector;

class Triangulation
{
public:
	// Getter
	Mat getPoints3D();

	// Others Methods
	void compute3Dpoints(vector<vector<Point2f> > points2DList, vector<Mat> projections);
	void print3Dpoints();
private:
	Mat points3D;
};
#endif /* INCLUDE_TRIANGULATION_HPP_ */
