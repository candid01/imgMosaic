/*
 * CameraParameters.hpp
 *  Created on: Jul 01, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef HEADERS_CAMERAPARAMETERS_HPP_
#define HEADERS_CAMERAPARAMETERS_HPP_

#include <iostream>
#include <math.h>
#include "opencv2/stitching/detail/camera.hpp"

using namespace cv::detail;
using cv::Mat;
using cv::Mat_;
using std::cos;
using std::sin;

class CameraParameters // class that has the intrinsic and extrinsic camera parameters
{
public:
	// Constructor
	CameraParameters(){};
	virtual ~CameraParameters(){};
	CameraParameters(int imgCols, int imgRows, float focalLength, float sensorSizeX, float sensorSizeY,
						float tx, float ty, float tz, float roll, float pitch, float yaw, float GSD);

	// Getters
	float  getMetersGSD();
	double getAspect();
	double getFocal();
	double getPpx();
	double getPpy();
	Mat    getRotation();
	Mat    getTranslation();

	// Setters
	void setMetersGSD(float gsd);
	void setAspect(double sx, double sy);
	void setFocal(double focalLength, double sx);
	void setPpx(double ppx);
	void setPpy(double ppy);
	void setRotation(float roll, float pitch, float yaw);
	void setTranslation(float tx, float ty, float tz);

	// Others Methods
	Mat	getIntrinsec();
	Mat getExtrinsec();
	Mat getProjection();
	void status();
private:
	float 		 metersGSD;
	CameraParams camera;
};
#endif /* HEADERS_CAMERAPARAMETERS_HPP_ */
