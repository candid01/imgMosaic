/*
 * Metadata.hpp
 *  Created on: Jun 29, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef METADATA_HPP_
#define METADATA_HPP_

#include <fstream>						// used to ifstream type in function-member
#include <iostream> 					// used to cout, endl in function-member
#include <math.h>						// import math libs
#include <sstream>  					// used stringstream in function-member;
#include <stdlib.h> 					// used to atof in function-member

using namespace std;

class Metadata 							// this class find the image metadatas in file
{
public:
	// Getters
	float  getTranlationX(); 			// return the translation x value
	float  getTranlationY();			// return the translation y value
	float  getTranlationZ();			// return the translation z value
	float  getDroll();					// return the rotation in axes x value in degree
	float  getDpitch();					// return the rotation in axes x value in degree
	float  getDyaw();					// return the rotation in axes x value in degree
	float  getRroll();					// return the rotation in axes x value in radians
	float  getRpitch();					// return the rotation in axes x value in radians
	float  getRyaw();					// return the rotation in axes x value in radians
	string getImgName();				// return image name

	// Others Methods
	void findMetadata(string imgName);	// get metadatas from the file
	void status();						// print the object status
protected:
	string imgName; 					// image name that this metadata came from
private:
	// Attributes
	float  Tx; 							// x translation, used the GPS coordinate Longitude
	float  Ty; 							// y translation, used the GPS coordinate Latitude
	float  Tz; 							// z translation, used the GPS high. This applies an scale in the image
	float  dRoll;						// angle for rotation axes x in degree
	float  dPitch;						// angle for rotation axes y in degree
	float  dYaw;						// angle for rotation axes z in degree
	float  rRoll;						// angle for rotation axes x in radians
	float  rPitch;						// angle for rotation axes y in radians
	float  rYaw;						// angle for rotation axes z in radians

	// Other Method
	float degree2radian(float degree); // convert Degree to Radians
};
#endif /* METADATA_HPP_ */
