/*
 * CameraParameters.cpp
 *  Created on: Jul 01, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../include/CameraParameters.hpp"

CameraParameters::CameraParameters(int imgCols, int imgRows, float focalLength, float sensorSizeX, float sensorSizeY,
								   float tx, float ty, float tz, float roll, float pitch, float yaw, float GSD)
{
	double sx, sy;

	this->metersGSD = 1 / GSD;
	this->camera.ppx = imgCols / 2;
	this->camera.ppy = imgRows / 2;

	sx = sensorSizeX / imgCols;
	sy = sensorSizeY / imgRows;

	this->camera.aspect = sy / sx;
	this->camera.focal  = focalLength / sx;

	this->setRotation(roll, pitch, yaw);
	this->setTranslation(tx, ty, tz);
}

// Getters
float CameraParameters::getMetersGSD()
{
	return this->metersGSD;
}

double CameraParameters::getAspect()
{
	return this->camera.aspect;
}

double CameraParameters::getFocal()
{
	return this->camera.focal;
}

double CameraParameters::getPpx()
{
	return this->camera.ppx;
}

double CameraParameters::getPpy()
{
	return this->camera.ppy;
}

Mat CameraParameters::getRotation()
{
	return this->camera.R;
}

Mat CameraParameters::getTranslation()
{
	return this->camera.t;
}


// Setters
void CameraParameters::setMetersGSD(float metersGSD)
{
	this->metersGSD = metersGSD;
}


void CameraParameters::setAspect(double sx, double sy)
{
	this->camera.aspect = sy / sx;
}


void CameraParameters::setFocal(double focalLength, double sx)
{
	this->camera.focal = focalLength / sx;
}


void CameraParameters::setPpx(double ppx)
{
	this->camera.ppx = ppx;
}


void CameraParameters::setPpy(double ppy)
{
	this->camera.ppy = ppy;
}


void CameraParameters::setRotation(float roll, float pitch, float yaw)
{
	double Roll_cos  = cos(roll),  Roll_sin  = sin(roll),
		   Pitch_cos = cos(pitch), Pitch_sin = sin(pitch),
		   Yaw_cos   = cos(yaw),   Yaw_sin   = sin(yaw);

	Mat Rx = (Mat_<double>(3,3) << 1        , 0      ,          0, 		  0, Roll_cos, Roll_sin,         0, -Roll_sin, Roll_cos	),
		Ry = (Mat_<double>(3,3) << Pitch_cos, 0      , -Pitch_sin, 		  0, 		1, 		  0, Pitch_sin, 		0, Pitch_cos),
		Rz = (Mat_<double>(3,3) << Yaw_cos  , Yaw_sin,          0, -Yaw_sin, Yaw_cos , 		  0, 		 0, 		0, 1		);

		Mat R = (Rx * Ry * Rz);
		R.convertTo(this->camera.R, CV_64F);
}


void CameraParameters::setRotation(Mat rotation)
{
	rotation.convertTo(this->camera.R, CV_64F);
}


void CameraParameters::setTranslation(float tx, float ty, float tz)
{
	Mat R_t = this->getRotation().t();
	Mat T   = (Mat_<double>(3,1) << tx, ty, tz);

	Mat a = (-R_t.row(0) * T);
	Mat b = (-R_t.row(1) * T);
	Mat c = (-R_t.row(2) * T);

	Mat trans = (Mat_<double>(3,1) << (a.at<double>(0, 0) * this->getMetersGSD()) / this->getFocal(),
									  (b.at<double>(0, 0) * this->getMetersGSD()) / this->getFocal(),
									  (c.at<double>(0, 0) * this->getMetersGSD()) / this->getFocal());

//	Mat trans = (Mat_<double>(3,1) << a.at<double>(0, 0),
//									  b.at<double>(0, 0),
//									  c.at<double>(0, 0));

	trans.convertTo(this->camera.t, CV_64F);
}


void CameraParameters::setTranslation(Mat translation)
{
	translation.convertTo(this->camera.t, CV_64F);
}


// Other Methods
Mat CameraParameters::getIntrinsec()
{
	return this->camera.K();
}


Mat	CameraParameters::getExtrinsec()
{
	Mat translation, extrinsec;
	hconcat(camera.R, camera.t, extrinsec);
	return extrinsec;
}


Mat CameraParameters::getProjection()
{
	return this->getIntrinsec() * this->getExtrinsec();
}


void CameraParameters::status()
{
	std::cout << "\t*** Camera Setup ***" << std::endl
			  << "Aspect:\t"	  << this->camera.aspect << std::endl
			  << "Focal:\t"		  << this->camera.focal  << std::endl
			  << "ppx:\t"		  << this->camera.ppx    << std::endl
			  << "ppy:\t"		  << this->camera.ppy    << std::endl
			  << "Rotation:\n"    << this->camera.R 	 << std::endl
			  << "Translation:\n" << this->camera.t		 << std::endl
			  << std::endl;
}
