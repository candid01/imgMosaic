#include <stdio.h>

#include "include/Features.hpp"
#include "include/Image.hpp"
#include "include/Match.hpp"
#include "include/SparseBundleAdjustment.hpp"
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


//-- Step4: Triangulation
	cout << "Calculating 3D points (Triangulation)." << endl;

	vector<Mat> projections;
	for(int i=0; i<numImages; i++)
			projections.push_back(img[i].getCamInfo().getProjection());

	Triangulation triang;
	triang.compute3Dpoints(match[0].getPoints2DList(), projections);


//-- Step5: Bundle Adjustment
	cout << "Sparse Bundle Adjustment (cvsba)." << endl;

	SparseBundleAdjustment sba;
	sba.runSBA(&triang, match, img, numImages);
	sba.printSBAError();


	return 0;
}
