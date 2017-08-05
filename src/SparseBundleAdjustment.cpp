/*
 * SparseBundleAjustment.cpp
 *  Created on: Aug 02, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#include "../include/SparseBundleAdjustment.hpp"

SparseBundleAdjustment::SparseBundleAdjustment()
{
	this->setSetupSBA(MOTION_3DPOINTS, 1500, 1e-10, 5, 5, false);
}

// Setter
void SparseBundleAdjustment::setSetupSBA(Sba::TYPE type, int iterations, double minError, int fixedIntrinsics, int fixedDistortion, bool verbose)
{
	this->setupSBA.type 			= type;
	this->setupSBA.iterations 		= iterations;
	this->setupSBA.minError 		= minError;
	this->setupSBA.fixedIntrinsics 	= fixedIntrinsics;
	this->setupSBA.fixedDistortion 	= fixedDistortion;
	this->setupSBA.verbose			= verbose;

	this->sba.setParams(setupSBA);
}


void SparseBundleAdjustment::runSBA(Triangulation *triang, Match *match, Image *imgs, int numImages)
{
	vector<Mat> intrinsec(numImages),
				R(numImages),
				T(numImages),
				distortion(numImages);

	vector<vector<int> > 	 visibility(numImages);
	vector< Point3f> 		 points3D(triang->getPoints3D().rows);
	vector<vector<Point2f> > points2D(numImages);

	for(int i=0; i<triang->getPoints3D().rows; i++)
		points3D[i] = Point3d(triang->getPoints3D().at<double>(i, 0), triang->getPoints3D().at<double>(i, 0), triang->getPoints3D().at<double>(i, 0));


	for(int i=0; i<numImages; i++)
		points2D[i].resize(triang->getPoints3D().rows);


	for(int i=0; i<triang->getPoints3D().rows; i++)
	{
		points2D[0][i] = Point2f(match->getPoints2DList()[0][i].x, match->getPoints2DList()[0][i].y);
		points2D[1][i] = Point2f(match->getPoints2DList()[1][i].x, match->getPoints2DList()[1][i].y);
	}


	for(int i=0; i<numImages; i++)
	{
		R[i] 		  = imgs[i].getCamInfo().getRotation();
		T[i] 		  = imgs[i].getCamInfo().getTranslation();
		intrinsec[i]  = imgs[i].getCamInfo().getIntrinsec();
		distortion[i] = Mat(5, 1, CV_64FC1, Scalar::all(0));

		visibility[i].resize(triang->getPoints3D().rows);

		for(int j=0; j<triang->getPoints3D().rows; j++)
			visibility[i][j] = 1;
	}

	sba.run(points3D, points2D, visibility, intrinsec, R, T, distortion);

	for(int i=0; i<numImages; i++)
	{
		imgs[i].getCamInfo().setTranslation(T[i]);
		imgs[i].getCamInfo().setRotation(R[i]);
	}
}


void SparseBundleAdjustment::status()
{
	cout << "\n\n*** SBA Parameters ***\n";

	if(this->setupSBA.type == MOTION_3DPOINTS)
		cout << "Type:\t\t\tMotion & 3DPoints" << endl;
	else
		if(this->setupSBA.type == JUST_MOTION)
			cout << "Type:\t\t\tJust Motion" << endl;
		else
			cout << "Type:\t\t\tJust 3DPoints" << endl;

	cout << "Iterations:\t\t"	  << this->setupSBA.iterations		<< endl
		 << "Min Error:\t\t"	  << this->setupSBA.minError		<< endl
		 << "Fixed Intrinsic:\t"  << this->setupSBA.fixedIntrinsics	<< endl
		 << "fixed Distortion:\t" << this->setupSBA.fixedDistortion	<< endl;
}


void SparseBundleAdjustment::printSBAError()
{
	cout << endl
		 << "Initial error = " << this->sba.getInitialReprjError() << endl
		 << "Final   error = " << this->sba.getFinalReprjError()   << endl
		 << endl;
}
