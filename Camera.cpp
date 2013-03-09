#include "Camera.h"

#include "WPILib.h"
#include <math.h>

Camera::Camera(bool verbose)
{
	a_verbose = verbose;
	
	ap_camera = &AxisCamera::GetInstance();
	
	ap_particles = NULL;
	a_highRect = 0, a_leftRect = 0, a_rightRect = 0;
	a_targetCenter = 0.0;
	a_distance = 0.0, a_angle = 0.0;
	a_side = false;
}

Camera::~Camera(void)
{
	delete ap_camera;
	ap_camera = NULL;
	
	imaqDispose(ap_particles);
}

void Camera::ProcessPicture(void)
{
	if(!ap_camera->IsFreshImage())
	{
		return;
	}
	
	double startTime = GetTime();
	
	HSLImage *hslImage = ap_camera->GetImage();
	MonoImage *monoImage = hslImage->GetLuminancePlane();
	Image *imaqImage = monoImage->GetImaqImage();
	
	int res;
	int width, height;
	
	res = imaqGetImageSize(imaqImage, &width, &height);
	CheckIMAQError(res, "imaqGetImageSize");

	res = imaqThreshold(imaqImage, imaqImage, 140, 255, 1, 255);
	CheckIMAQError(res, "imaqThreshold");

//	res = imaqRejectBorder(imaqImage, imaqImage, 1);
//	CheckIMAQError(res, "imaqRejectBorder");

	res = imaqConvexHull(imaqImage, imaqImage, 1);
	CheckIMAQError(res, "imaqConvexHull");

	StructuringElement element;
	element.matrixRows = 7;
	element.matrixCols = 7;
	element.hexa = FALSE;
	// element.kernel = new int[49];

	res = imaqMorphology(imaqImage, imaqImage, IMAQ_DILATE, &element);
	CheckIMAQError(res, "imaqMorphology");

	res = imaqEqualize(imaqImage, imaqImage, 0, 255, NULL);
	CheckIMAQError(res, "imaqEqualize");
	
	int numMeasures = 5;
	MeasurementType measures[5] =
	{
		IMAQ_MT_CENTER_OF_MASS_X,
		IMAQ_MT_CENTER_OF_MASS_Y,
		IMAQ_MT_BOUNDING_RECT_WIDTH,
		IMAQ_MT_BOUNDING_RECT_HEIGHT,
		IMAQ_MT_AREA,
	};

	int numParticles;
	if(ap_particles != NULL)
	{
		res = imaqDispose(ap_particles);
		CheckIMAQError(res, "imaqDispose(ap_particles)");
	}

	res = imaqCountParticles(imaqImage,
							 1,
							 &numParticles);
	CheckIMAQError(res, "imaqCountParticles");

	ap_particles = imaqMeasureParticles(imaqImage,
										IMAQ_CALIBRATION_MODE_PIXEL,
										measures,
										numMeasures);
	if(ap_particles == NULL) {
		CheckIMAQError(0, "imaqMeasureParticles");
	}

	printf("ap_particles 1 %p\n", ap_particles);


	if(a_verbose)
	{
		printf("%d particle(s) found\n", numParticles);
		printf("Candidate target particles:\n\n");
	}

	int highParticle = -1;
	int leftParticle = -1;
	int rightParticle = -1;
	for(int i = 0; i < numParticles; i++)
	{
		double area = ap_particles->pixelMeasurements[i][4];

		if(area > 900.0)
		{
			double w = ap_particles->pixelMeasurements[i][2];
			double h = ap_particles->pixelMeasurements[i][3];

			if(w/h > 0.8 && w/h < 2.0)
			{
				double cX = ap_particles->pixelMeasurements[i][0];
				double cY = ap_particles->pixelMeasurements[i][1];

				if(highParticle == -1)
				{
					highParticle = i;
					leftParticle = i;
					rightParticle = i;
				}
				else
				{
					if(cY < ap_particles->pixelMeasurements[highParticle][1])
						highParticle = i;
					if(cX < ap_particles->pixelMeasurements[leftParticle][0])
						leftParticle = i;
					if(cX > ap_particles->pixelMeasurements[rightParticle][0])
						rightParticle = i;
				}
				
				if(a_verbose)
				{
					printf("==== Particle %d\n", i);
					printf("\tCenter: (%f, %f)\n", cX, cY);
					printf("\tWidth/Height: %f\n", w/h);
					printf("\tArea: %f\n", area);
					printf("\n");
				}
			}
		}
	}

	if(a_verbose)
	{
		printf("highParticle: %d\n", highParticle);
		printf("leftParticle: %d\n", leftParticle);
		printf("rightParticle: %d\n", rightParticle);
		printf("\n");
	}
	a_highRect = highParticle;
	a_leftRect = leftParticle;
	a_rightRect = rightParticle;

	res = imaqDispose(imaqImage);
	CheckIMAQError(res, "imaqDispose(inputImage)");
	
	delete hslImage;
	hslImage = NULL;
	
	delete monoImage;
	monoImage = NULL;
	
	double endTime = GetTime();
	if(a_verbose)
	{
		printf("Total time: %f\n ", endTime-startTime);
	}
}

void Camera::ProcessRectangles(void)
{
	if(ap_particles != NULL){
	double highParticleX = ap_particles->pixelMeasurements[a_highRect][0];
	double highParticleY = ap_particles->pixelMeasurements[a_highRect][1];
	double leftParticleX = ap_particles->pixelMeasurements[a_leftRect][0];
	double leftParticleY = ap_particles->pixelMeasurements[a_leftRect][1];
	double rightParticleX = ap_particles->pixelMeasurements[a_rightRect][0];
	double rightParticleY = ap_particles->pixelMeasurements[a_rightRect][1];

	double targetIntersectX = highParticleX;
	double targetIntersectY = (leftParticleY + rightParticleY)/2.0;

	double targetHeight = targetIntersectY - highParticleY;
	double targetLeftWidth = sqrt(pow(targetIntersectX-leftParticleX, 2) + pow(targetIntersectY-leftParticleY, 2));
	double targetRightWidth = sqrt(pow(targetIntersectX-rightParticleX, 2) + pow(targetIntersectY-rightParticleY, 2));
	
	if(targetLeftWidth < targetRightWidth)	// Right of centerline
	{
		a_side = true;
	}
	else									// Left of centerline
	{
		a_side = false;
	}

	a_targetCenter = highParticleX;

	if(a_verbose)
	{
		printf("targetHeight: %f\n", targetHeight);
		printf("targetLeftWidth: %f\n", targetLeftWidth);
		printf("targetRightWidth: %f\n", targetRightWidth);
	}

	double targetDistance = KV * 18.5 / targetHeight * 12.0;
	
	if(a_verbose)
	{
		printf("targetDistance: %f\n", targetDistance);
	}

	double L = 27.38 / 2.0;
	double leftLPrime = targetLeftWidth * targetDistance / (KH * 12);
	double rightLPrime = targetRightWidth * targetDistance / (KH * 12);
	double leftB = atan(leftLPrime / targetDistance);
	double rightB = atan(rightLPrime / targetDistance);
	printf("leftB: %f\n" , leftB);
	double leftX;
	double rightX;
	if(a_side)	// Right of centerline
	{
		leftX = targetDistance * cos(leftB) + sqrt(pow(L, 2) - pow(targetDistance, 2) * pow(sin(leftB), 2));
		rightX = targetDistance * cos(rightB) - sqrt(pow(L, 2) - pow(targetDistance, 2) * pow(sin(rightB), 2));
	}
	else		// Left of centerline
	{
		leftX = targetDistance * cos(leftB) - sqrt(pow(L, 2) - pow(targetDistance, 2) * pow(sin(leftB), 2));
		rightX = targetDistance * cos(rightB) + sqrt(pow(L, 2) - pow(targetDistance, 2) * pow(sin(rightB), 2));
	}
	
	double leftTheta = acos((pow(leftX, 2)*(-1) + pow(targetDistance, 2) + pow(L, 2))/(2*targetDistance*L));
	double rightTheta = acos((pow(rightX, 2)*(-1) + pow(targetDistance, 2) + pow(L, 2))/(2*targetDistance*L));
	
	double leftAngle;
	double rightAngle;
	if(a_side)	// Right of centerline
	{
		leftAngle = (leftTheta*180.0/PI) - 90.0;
		rightAngle = 90.0 - (rightTheta*180.0/PI);
	}
	else		// Left of centerline
	{
		leftAngle = 90.0 - (leftTheta*180.0/PI);
		rightAngle = (rightTheta*180.0/PI) - 90.0;
	}

	double avgAngle = (leftAngle + rightAngle) / 2.0;

	if(a_verbose)
	{
		printf("leftAngle: %f\n", leftAngle);
		printf("rightAngle: %f\n", rightAngle);
		printf("avgAngle: %f\n", avgAngle);
	}
	
	a_distance = targetDistance;
	a_angle = avgAngle;
	
	}
	else{
		printf("Process Rect - no particles\n");
	}
}

void Camera::CheckIMAQError(int res, const char *desc)
{
	if(res == 0)
	{
		int error = imaqGetLastError();
		printf("IMAQ Error: %s, %d\n", desc, error);
	}
}
