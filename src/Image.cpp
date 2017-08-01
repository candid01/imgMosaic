/*
 * Image.cpp
 *  Created on: Jun 30, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../include/Image.hpp"

// Getter
CameraParameters Image::getCamInfo()
{
	return this->camInfo;
}

Mat Image::getImage(){
	return this->image;
}

// Setter
void Image::setCamInfo(CameraParameters camInfo)
{
	this->camInfo = camInfo;
}

void Image::setImage(Mat image)
{
	this->image = image;
}

// Other Methods
void Image::openImg(string path)
{
	Mat src = imread(path);

	if(src.empty()){
		cout << "Error reading image from " << path << endl;
		return;
	}

	this->setImage(src);
	this->imgName = path;
	this->findMetadata(this->getImgName());

	CameraParameters camera(
									this->getImage().cols,
									this->getImage().rows,
									3.6f, 					 // Focal Length
									6.16f,					 // Sensor Size in X
									4.62f,					 // Sensor Size in Y
									this->getTranlationX(),
									this->getTranlationY(),
									this->getTranlationZ(),
									this->getRroll(),
									this->getRpitch(),
									this->getRyaw(),
									0.04f					 // how many pixels to complete 1 meter, based on GSD
							   );

	this->camInfo = camera;
	camera.~CameraParameters();
}

void Image::saveImg(string path)
{
	imwrite(path + this->getImgName(), this->getImage());
}

void Image::showImg()
{
	namedWindow("Showing Image " + this->getImgName(), WINDOW_NORMAL);
	imshow("Showing Image " + this->getImgName(), this->getImage());
	waitKey(0);
}

void Image::status(bool cameraStatus){
	Metadata::status();

	if(cameraStatus)
		this->camInfo.status();
}
