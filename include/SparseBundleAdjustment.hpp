/*
 * SparseBundleAdjustment.hpp
 *  Created on: Aug 02, 2017
 *      Author: Leandro Candido
 *       Email: l.candido@usp.br
 */
#ifndef SPARSEBUNDLEADJUSTMENT_HPP_
#define SPARSEBUNDLEADJUSTMENT_HPP_

#include <cvsba.h>											// using to import sba functions
#include "../include/Match.hpp"								// using to import 2D image points
#include "../include/Triangulation.hpp"						// using to import 3D world points
#include "../include/Image.hpp"								// using to import translation and rotation from each image

#define MOTION_3DPOINTS cvsba::Sba::MOTIONSTRUCTURE			// used to specify the sba will correct 3DPoints and extrinsics
#define JUST_MOTION 	cvsba::Sba::MOTION					// used to specify the sba will correct just extrinsics
#define JUST_3DPOINTS 	cvsba::Sba::STRUCTURE				// used to specify the sba will correct just 3DPoints

using cv::Mat;
using std::cout;
using std::endl;
using std::vector;
using namespace cvsba;


class SparseBundleAdjustment								// this class compute the sba
{
public:
	SparseBundleAdjustment();								// constructor
	virtual ~SparseBundleAdjustment(){};					// destructor

	// Setter
	void setSetupSBA(										// this function setup the Sba::Params to execute the run from cvsba
					Sba::TYPE type,							// type of sba: MOTION_3DPOINTS, JUST_MOTION, JUST_3DPOINTS
					int		  iterations,					// maximum number of iterations (stop criteria)
					double	  minError,						// minimum error acceptable     (stop criteria)
					int		  fixedIntrinsics,				// number of intrinsics parameters that keep fixed [0-5] (fx, cx, cy, fy/fx, s )
					int		  fixedDistortion,				// number of distortion parameters that keep fixed [0-5] (k1, k2, p1,   p2,  k3)
					bool 	  verbose						// print sba details in computing process
					);

	// Other Methods
	void runSBA(											// this function realizes the transition and rotation corrections
				Triangulation *triang,						// 3D world points x, y,z
				Match		  *match,						// 2D image points x, y
				Image		  *imgs,						// images set to catch translation and rotation
				int			   numImages					// number of images used to compute the SBA
			   );

	void	status();										// print the parameter values used to configure the sba
	void	printSBAError();								// print the initial and final error calculate in sba
private:
	Sba::Params setupSBA;									// this attribute is used to configure the sba attribute
	Sba		    sba;										// this attribute is used to compute the sba using cvsba
};
#endif /* SPARSEBUNDLEADJUSTMENT_HPP_ */
