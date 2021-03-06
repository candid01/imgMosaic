/*
 * Image.hpp
 *  Created on: Jun 30, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef IMAGE_CPP_
#define IMAGE_CPP_

#include "opencv2/highgui.hpp"  				// using to show image in member-function
#include <string>			    				// import class string
#include "../include/CameraParameters.hpp" 		// import class CameraParameters
#include "../include/Metadata.hpp" 	    		// import class Metadata

using namespace cv;

class Image : public Metadata					// class image extends from Metadata
{
public:
	// Getters
	Mat  			 getImage();				// function that get the image
	CameraParameters getCamInfo();				// function that get the camera information

	// Setters
	void setImage(Mat image); 					// function that setup the image
	void setCamInfo(CameraParameters camInfo);	// function that setup the camera information

	// Other Methods
	void openImg(string path); 					// open the image from directory
	void saveImg(string path); 					// save the image on directory
	void showImg(); 		   					// show the image on screen
	void status(bool cameraStatus);				// print the image status
private:
	Mat 			 image; 					// image
	CameraParameters camInfo;					// camera information
};
#endif /* IMAGE_CPP_ */
