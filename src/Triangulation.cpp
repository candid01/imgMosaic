/*
 * Triangulation.cpp
 *  Created on: Jul 05, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../headers/Triangulation.hpp"

// Getter
Mat Triangulation::getPoints3D()
{
	return this->points3D;
}


// Others Methods
void Triangulation::compute3Dpoints(vector<vector<Point2f> > points2DList, vector<Mat> projections)
{
	Mat auxMat1, auxMat2;
	vector<Mat> points2D;

	// Create a vector to be sent to triangulation when it happens 3 matches
	for(int i=0; (unsigned)i<points2DList.size(); i=i+2)
	{
		auxMat1 = cv::Mat_<double>(2, points2DList[i].size());
		auxMat2 = cv::Mat_<double>(2, points2DList[i].size());

		for(int j=0; (unsigned)j<points2DList[i].size(); j++){
			auxMat1.at<double>(0, j) = points2DList[ i ][j].x;
			auxMat1.at<double>(1, j) = points2DList[ i ][j].y;

			auxMat2.at<double>(0, j) = points2DList[i+1][j].x;
			auxMat2.at<double>(1, j) = points2DList[i+1][j].y;
		}

		points2D.push_back(auxMat1);
		points2D.push_back(auxMat2);

		auxMat1.release();
		auxMat2.release();
	}

	triangulatePoints(points2D, projections, this->points3D);
	transpose(this->points3D, this->points3D);
}

void Triangulation::print3Dpoints()
{
	std::cout << std::endl;
	for(int i=0; i<(int)this->getPoints3D().rows; i++)
		printf("[%2d] %.4lf \t%.4lf \t%.4lf\n", i,
				this->points3D.at<double>(i, 0), this->points3D.at<double>(i, 1), this->points3D.at<double>(i, 2));
	std::cout << std::endl;
}
