#include <stdio.h>

#include <cvsba.h>
#include "include/Features.hpp"
#include "include/Image.hpp"
#include "include/Match.hpp"
#include "include/Triangulation.hpp"

using namespace std;
using namespace cv;

#define MIN_HESSIAN 400

int main(int argc, char **argv)
{
	int numImages = argc - 1;

//-- Step1: Loading Images
	cout << "Opening Images and Calculating Camera Parameters." << endl;
	Image img[numImages];

	for(int i=0; i<numImages; i++)
		img[i].openImg(argv[i+1]);


//-- Step2: Features Extractor
	cout << "Finding Features from images." << endl;
	Features features[numImages];

	for(int i=0; i<numImages; i++)
		features[i].computeKeypointsAndDescriptors_SURF(MIN_HESSIAN, img[i].getImage());


//-- Step3: Features Matching
	cout << "Calculating Features Matches." << endl;
	Match match[numImages-1];

	for(int i=0;i<numImages-1; i++)
		match[i].findMatches(features[i].getDescriptors(), features[i+1].getDescriptors(), features[i].getKeypoints(), features[i+1].getKeypoints());

//	match[0].printKeypointsMetched();



//-- Step4: Triangulation
	cout << "Calculating 3D points (Triangulation)." << endl;

	vector<Mat> projections;
	for(int i=0; i<numImages; i++)
			projections.push_back(img[i].getCamInfo().getProjection());

	Triangulation triang;
	triang.compute3Dpoints(match[0].getPoints2DList(), projections);
	triang.print3Dpoints();





//-- Step5: Bundle Adjustment
	cout << "Sparse Bundle Adjustment (cvsba)." << endl;

	vector<Mat> intrinsec(numImages),
				R(numImages),
				T(numImages),
				distortion(numImages);

	vector<vector<int> > 	 visibility(numImages);
	vector< Point3d > 		 points3D(triang.getPoints3D().rows);
	vector<vector<Point2d> > points2D(numImages);

	for(int i=0; i<triang.getPoints3D().rows; i++)
		points3D[i] = Point3d(triang.getPoints3D().at<double>(i, 0), triang.getPoints3D().at<double>(i, 0), triang.getPoints3D().at<double>(i, 0));


	for(int i=0; i<numImages; i++)
		points2D[i].resize(triang.getPoints3D().rows);



	for(int i=0; i<triang.getPoints3D().rows; i++)
	{
		points2D[0][i] = Point2d(match[0].getPoints2DList()[0][i].x, match[0].getPoints2DList()[0][i].y);
		points2D[1][i] = Point2d(match[0].getPoints2DList()[1][i].x, match[0].getPoints2DList()[1][i].y);
	}

	cvsba::Sba::Params a;

	a.type 			  = cvsba::Sba::MOTIONSTRUCTURE;
//	a.type 			  = cvsba::Sba::MOTION;
//	a.type 			  = cvsba::Sba::STRUCTURE;
	a.iterations 	  = 1500;
	a.minError 		  = 1e-10;
	a.fixedIntrinsics = 5;
	a.fixedDistortion = 5;
	// a.verbose 		  = true;

	cvsba::Sba sba;
	sba.setParams(a);


	for(int i=0; i<numImages; i++)
	{
		R[i] 		  = img[i].getCamInfo().getRotation();
		T[i] 		  = img[i].getCamInfo().getTranslation();
		intrinsec[i]  = img[i].getCamInfo().getIntrinsec();
		distortion[i] = Mat(5, 1, CV_64FC1, Scalar::all(0));

		visibility[i].resize(triang.getPoints3D().rows);

		for(int j=0; j<triang.getPoints3D().rows; j++)
			visibility[i][j] = 1;
	}

	sba.run(points3D, points2D, visibility, intrinsec, R, T, distortion);

	cout << "\nInitial error\t= " << sba.getInitialReprjError() << endl
		 << "Final error\t= " 	  << sba.getFinalReprjError()   << endl
		 << endl;











//-- Final Step
	cout << "\nFINISH HIM!!!" << endl;
	return 0;
}
