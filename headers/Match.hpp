/*
 * Mach.hpp
 *  Created on: Jul 04, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef HEADERS_MATCH_HPP_
#define HEADERS_MATCH_HPP_

#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <stdio.h>

#include "Features.hpp"

using cv::DMatch;
using cv::KeyPoint;
using cv::Mat;
using cv::Point2f;
using std::vector;

class Match
{
public:
	// Getters
	vector<DMatch> getMaches();
	vector<vector<Point2f> > getPoints2DList();

	// Setters
	void setMaches(vector<DMatch> matches);


	// Others Methods
	void findMatches(Mat descrip1, Mat descrip2, vector<KeyPoint> key1, vector<KeyPoint> key2);
	void printKeypointsMetched();
	void drawMatches(Mat img_1, Mat img_2, vector<KeyPoint> key1, vector<KeyPoint> key2);
private:
	vector<DMatch>   		 maches;
	vector<vector<Point2f> > points2DList;
};
#endif /* HEADERS_MATCH_HPP_ */
