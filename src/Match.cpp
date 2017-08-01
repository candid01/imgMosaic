/*
 * Mach.Cpp
 *  Created on: Jul 04, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../include/Match.hpp"

// Getter
vector<DMatch> Match::getMaches()
{
	return this->maches;
}

vector<vector<Point2f> > Match::getPoints2DList()
{
	return this->points2DList;
}


// Setter
void Match::setMaches(vector<DMatch> matches)
{
	this->maches = matches;
}


// Others Methods
void Match::findMatches(Mat descrip1, Mat descrip2, vector<KeyPoint> key1, vector<KeyPoint> key2)
{
	double			      min_dist = 100;
	cv::FlannBasedMatcher matcher;
	vector<DMatch>	  	  matches;

	matcher.match(descrip1, descrip2, matches);

	//-- Quick calculation of max and min distances between keypoints
	for(int i=0; i<descrip1.rows; i++)
	{
		double dist = matches[i].distance;
	    if(dist < min_dist)
	    	min_dist = dist;
	}

	vector<DMatch> good_matches;
	for(int i=0; i<descrip1.rows; i++)
	{
		if(matches[i].distance <= std::max(2*min_dist, 0.02))
			good_matches.push_back(matches[i]);
	}

	this->setMaches(good_matches);

	this->points2DList.push_back(vector<Point2f>());
	this->points2DList.push_back(vector<Point2f>());

	for(int i=0; i<(int)this->getMaches().size(); i++)
	{
		points2DList[0].push_back(key1[this->getMaches()[i].queryIdx].pt);
		points2DList[1].push_back(key2[this->getMaches()[i].trainIdx].pt);
	}
}

void Match::printKeypointsMetched()
{
	std::cout << std::endl;
	for(int i=0; i<(int)this->getMaches().size(); i++){
		printf("[%2d] Keypoint 1: %.8lf\t%.8lf\t\tKeypoint 2: %.8lf\t%.8lf\n", i,
				this->points2DList[0][i].x, this->points2DList[0][i].y,
				this->points2DList[1][i].x, this->points2DList[1][i].y);
	}
	std::cout << std::endl;
}

void Match::drawMatches(Mat img_1, Mat img_2, vector<KeyPoint> key1, vector<KeyPoint> key2)
{
	Mat img_matches;
	cv::drawMatches(
						img_1,
						key1,
						img_2,
						key2,
						this->getMaches(),
						img_matches,
						cv::Scalar::all(-1),
						cv::Scalar::all(-1),
						vector<char>(),
						cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
				   );

	cv::imwrite("Matches.JPG", img_matches);
}
