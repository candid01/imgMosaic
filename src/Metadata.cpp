/*
 * Metadata.cpp
 *  Created on: Jun 29, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */

#include "../headers/Metadata.hpp"


// Getters
float Metadata::getTranlationX()
{
	return this->Tx;
}

float Metadata::getTranlationY()
{
	return this->Ty;
}

float Metadata::getTranlationZ()
{
	return this->Tz;
}

float Metadata::getDroll()
{
	return this->dRoll;
}

float Metadata::getDpitch()
{
	return this->dPitch;
}

float Metadata::getDyaw()
{
	return this->dYaw;
}

float Metadata::getRroll()
{
	return this->rRoll;
}

float Metadata::getRpitch()
{
	return this->rPitch;
}

float Metadata::getRyaw()
{
	return this->rYaw;
}

string Metadata::getImgName()
{
	return this->imgName;
}


// Others Methods
float Metadata::degree2radian(float degree)
{
	return degree * (M_PI / 180);
}

void Metadata::findMetadata(string imgName)
{
	int num_rows = 52,
		num_cols = 16;

	string data[num_rows][num_cols];
	ifstream file("Metadatas.csv");		// open the table where are Pitch, Roll, Yaw and distances informagem for each image

	// do parse from information and storage in data
	for(int rows=0; rows<num_rows; ++rows)
	{
		string line;
		getline(file, line);

		if(!file.good()) break;

		stringstream iss(line);
		for(int cols=0; cols<num_cols; ++cols)
		{
			string val;
			getline(iss, val, ';');
			if(!iss.good()) break;

			data[rows][cols] = val;
		}
	}

	// convert data from all images (string to float)
	for(int i=0; i<num_rows; i++){
		if(!data[i][0].compare(imgName)){
			this->Tx 	 = atof(data[i][10].c_str());
			this->Ty 	 = atof(data[i][11].c_str());
			this->Tz 	 = atof(data[i][12].c_str());

			this->dRoll  = atof(data[i][13].c_str());
			this->dPitch = atof(data[i][14].c_str()) + 90;
			this->dYaw   = atof(data[i][15].c_str());

			this->rRoll  = degree2radian(this->dRoll);
			this->rPitch = degree2radian(this->dPitch);
			this->rYaw   = degree2radian(this->dYaw);
		}
	}
}

void Metadata::status()
{
	cout << "Image:\t\t\t" << this->getImgName() << endl;

	cout << "Translation [m]:\t[" << this->getTranlationX() << ", "
								  << this->getTranlationY() << ", "
								  << this->getTranlationZ() << "]"
								  << endl;

	cout << "Angles [°]:\t\t[" << this->getDroll()  << ", "
							     << this->getDpitch() << ", "
								 << this->getDyaw()   << "]"
								 << endl;

	cout << "Angles [rad]:\t\t[" << this->getRroll()  << ", "
								   << this->getRpitch() << ", "
								   << this->getRyaw()   << "]"
								   << endl << endl;
}
