#include "ImageProcessor.h"
 
// If you call Machine Vision functions in your script, add NIMachineVision.c to the project.

ImageProcessor::ImageProcessor(bool verbose){

	IP = "192.168.0.90";
	ap_camera = &AxisCamera::GetInstance(IP);
	if(ap_camera == NULL){
		printf("NO CAMERA DETECTED");
	}
	a_verbose = verbose;
	
}

ImageProcessor::~ImageProcessor(){
	delete ap_camera;
	ap_camera = NULL;
}

int ImageProcessor::getRectangles(){
	if(!ap_camera->IsFreshImage()){
		return 2;
	}
	
	//double startTime = GetTime();
	
	HSLImage *hslImage = ap_camera->GetImage();
	

// Image *image;
// imaqReadFile(image, "Template1.png", NULL, NULL);
	

	 MonoImage *monoImage = hslImage->GetLuminancePlane();
	 Image *image = monoImage->GetImaqImage();
	
	
	
	int success = IVA_ProcessImage(image);

	if(a_verbose){
		//double time = GetTime() - startTime;
		//printf("Image Processed In: %d \n", time);
	}
	
	return success;

	
}

int ImageProcessor::IVA_ProcessImage(Image *image)
{
	int success = 1;
    IVA_Data *ivaData;
    int pKernel[9] = {1,1,1,1,1,1,1,1,1};
    StructuringElement structElem;

    // Initializes internal data (buffers and array of points for caliper measurements)
    VisionErrChk(ivaData = IVA_InitData(4, 0));

	VisionErrChk(IVA_CLRThreshold(image, 0, 60, 0, 60, 0, 60, IMAQ_RGB));

    //-------------------------------------------------------------------//
    //                  Advanced Morphology: Convex Hull                 //
    //-------------------------------------------------------------------//

    // Computes the convex envelope for each labeled particle in the source image.
    VisionErrChk(imaqConvexHull(image, image, TRUE));

    //-------------------------------------------------------------------//
    //                Advanced Morphology: Remove Objects                //
    //-------------------------------------------------------------------//

    structElem.matrixCols = 3;
    structElem.matrixRows = 3;
    structElem.hexa = FALSE;
    structElem.kernel = pKernel;

    // Filters particles based on their size.
    VisionErrChk(imaqSizeFilter(image, image, TRUE, 5, IMAQ_KEEP_LARGE, &structElem));

	VisionErrChk(IVA_MatchShape(image, 
		"Template1.png", 
		380, TRUE, ivaData, 3));

    // Releases the memory allocated in the IVA_Data structure.
    IVA_DisposeData(ivaData);

Error:
	return success;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_CLRThreshold
//
// Description  : Thresholds a color image.
//
// Parameters   : image      -  Input image
//                min1       -  Minimum range for the first plane
//                max1       -  Maximum range for the first plane
//                min2       -  Minimum range for the second plane
//                max2       -  Maximum range for the second plane
//                min3       -  Minimum range for the third plane
//                max3       -  Maximum range for the third plane
//                colorMode  -  Color space in which to perform the threshold
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
 int ImageProcessor::IVA_CLRThreshold(Image* image, int min1, int max1, int min2, int max2, int min3, int max3, int colorMode)
{
    int success = 1;
    Image* thresholdImage;
    Range plane1Range;
    Range plane2Range;
    Range plane3Range;


    //-------------------------------------------------------------------//
    //                          Color Threshold                          //
    //-------------------------------------------------------------------//

    // Creates an 8 bit image for the thresholded image.
    VisionErrChk(thresholdImage = imaqCreateImage(IMAQ_IMAGE_U8, 7));

    // Set the threshold range for the 3 planes.
    plane1Range.minValue = min1;
    plane1Range.maxValue = max1;
    plane2Range.minValue = min2;
    plane2Range.maxValue = max2;
    plane3Range.minValue = min3;
    plane3Range.maxValue = max3;

    // Thresholds the color image.
    VisionErrChk(imaqColorThreshold(thresholdImage, image, 1, IMAQ_HSL, &plane1Range, &plane2Range, &plane3Range));

    // Copies the threshold image in the souce image.
    VisionErrChk(imaqDuplicate(image, thresholdImage));

Error:
    imaqDispose(thresholdImage);

    return success;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_MatchShape
//
// Description  : Finds a shape in an image.
//
// Parameters   : image            -  Input image
//                templatePath     -  Template image path
//                minimumScore     -  Minimum score a match can have for the
//                                    function to consider the match valid.
//                scaleInvariance  -  If TRUE, searches for shapes regardless of size.
//                ivaData          -  Internal Data structure
//                stepIndex        -  Step index (index at which to store the results in the resuts array)
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
 int ImageProcessor::IVA_MatchShape(Image* image,
                                   char* templatePath,
                                   double minimumScore,
                                   int scaleInvariance,
                                   IVA_Data* ivaData,
                                   int stepIndex)
{
    int success = TRUE;
    Image* shapeImage;
    Image* imageTemplate;
    int i,j;
    short lookupTable[256];
    ShapeReport* shapeReport = NULL;
    int numMatchesFound;
    PointFloat centroid;
    int numMatches = 0;
    int numObjectResults;
    IVA_Result* shapeResults;
    unsigned int visionInfo;
    TransformReport* realWorldPosition = NULL;


    //-------------------------------------------------------------------//
    //                           Shape Matching                          //
    //-------------------------------------------------------------------//

    // Creates a temporary image that will be used to perform the search.
    VisionErrChk(shapeImage = imaqCreateImage(IMAQ_IMAGE_U8, 7));

    // Applies a lookup table to the image because the input image for the
    // imaqMatchShape fucntion must be a binary image that contains only
    // pixel values of 0 or 1

    lookupTable[0] = 0;
    for (i = 1 ; i < 256 ; i++)
        lookupTable[i] = 1;

    VisionErrChk(imaqLookup(shapeImage, image, lookupTable, NULL));

    // Creates and read the image template containing the shape to match
    VisionErrChk(imageTemplate = imaqCreateImage(IMAQ_IMAGE_U8, 7));
    VisionErrChk(imaqReadFile(imageTemplate, templatePath, NULL, NULL));

    // Applies the same lookup table to obtain an image containing only pixel
    // values of 0 and 1.
    VisionErrChk(imaqLookup(imageTemplate, imageTemplate, lookupTable, NULL));

    // Finds the shape in the binary image.
    VisionErrChk(shapeReport = imaqMatchShape(shapeImage, shapeImage, imageTemplate, scaleInvariance, 1, 0.5, &numMatchesFound));

    // Log the results in the points array for future caliper operations.
    for (i = 0 ; i < numMatchesFound ; i++)
    {
        if (shapeReport[i].score >= minimumScore)
            numMatches++;
    }

    // ////////////////////////////////////////
    // Store the results in the data structure.
    // ////////////////////////////////////////
    
    // First, delete all the results of this step (from a previous iteration)
    IVA_DisposeStepResults(ivaData, stepIndex);

    // Check if the image is calibrated.
    VisionErrChk(imaqGetVisionInfoTypes(image, &visionInfo));

    // If the image is calibrated, we also need to log the calibrated position (x and y) -> 5 results instead of 3
    numObjectResults = (visionInfo & IMAQ_VISIONINFO_CALIBRATION ? 5 : 3);
        
    ivaData->stepResults[stepIndex].numResults = numMatches * numObjectResults + 1;
    ivaData->stepResults[stepIndex].results = (IVA_Result*) malloc(sizeof(IVA_Result) * ivaData->stepResults[stepIndex].numResults);
	//realloc(ivaData->stepResults[stepIndex].results, sizeof(IVA_Result) * ivaData->stepResults[stepIndex].numResults);
    if(ivaData->stepResults[stepIndex].results != NULL){
    	printf("Results Allocated\n");
    }
    shapeResults = ivaData->stepResults[stepIndex].results;
    
    if (shapeResults)
    {
        #if defined (IVA_STORE_RESULT_NAMES)
            sprintf(shapeResults->resultName, "# Matches");
        #endif
        shapeResults->type = IVA_NUMERIC;
        shapeResults->resultVal.numVal = numMatches;
        shapeResults++;
        
        j = 0;
        
        for (i = 0 ; i < numMatchesFound ; i++)
        {
            if (shapeReport[i].score >= minimumScore)
            {
                j++;
                    
                #if defined (IVA_STORE_RESULT_NAMES)
                    sprintf(shapeResults->resultName, "Match %d.X Position (Pix.)", j);
                #endif
                shapeResults->type = IVA_NUMERIC;
                shapeResults->resultVal.numVal = shapeReport[i].centroid.x;
                shapeResults++;
            
                #if defined (IVA_STORE_RESULT_NAMES)
                    sprintf(shapeResults->resultName, "Match %d.Y Position (Pix.)", j);
                #endif
                shapeResults->type = IVA_NUMERIC;
                shapeResults->resultVal.numVal = shapeReport[i].centroid.y;
                shapeResults++;

                if (visionInfo & IMAQ_VISIONINFO_CALIBRATION)
                {
                    centroid.x = shapeReport[i].centroid.x;
                    centroid.y = shapeReport[i].centroid.y;
                    realWorldPosition = imaqTransformPixelToRealWorld(image, &centroid, 1);
                
                    #if defined (IVA_STORE_RESULT_NAMES)
                        sprintf(shapeResults->resultName, "Match %d.X Position (World)", j);
                    #endif
                    shapeResults->type = IVA_NUMERIC;
                    shapeResults->resultVal.numVal = realWorldPosition->points[0].x;
                    shapeResults++;
	
                    #if defined (IVA_STORE_RESULT_NAMES)
                        sprintf(shapeResults->resultName, "Match %d.Y Position (World)", j);
                    #endif
                    shapeResults->type = IVA_NUMERIC;
                    shapeResults->resultVal.numVal = realWorldPosition->points[0].y;
                    shapeResults++;
                }

                #if defined (IVA_STORE_RESULT_NAMES)
                    sprintf(shapeResults->resultName, "Match %d.Score", j);
                #endif
                shapeResults->type = IVA_NUMERIC;
                shapeResults->resultVal.numVal = shapeReport[i].score;
                shapeResults++;
            }
        }
    }

Error:
    // Disposes temporary image and structures.
    imaqDispose(imageTemplate);
    imaqDispose(shapeImage);
    imaqDispose(shapeReport);
    imaqDispose(realWorldPosition);

    return success;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_InitData
//
// Description  : Initializes data for buffer management and results.
//
// Parameters   : # of steps
//                # of coordinate systems
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
 IVA_Data* ImageProcessor::IVA_InitData(int numSteps, int numCoordSys)
{
    int success = 1;
    IVA_Data* ivaData = NULL;
    int i;


    // Allocate the data structure.
    VisionErrChk(ivaData = (IVA_Data*)malloc(sizeof (IVA_Data)));

    // Initializes the image pointers to NULL.
    for (i = 0 ; i < IVA_MAX_BUFFERS ; i++)
        ivaData->buffers[i] = NULL;

    // Initializes the steo results array to numSteps elements.
    ivaData->numSteps = numSteps;

    ivaData->stepResults = (IVA_StepResults*)malloc(ivaData->numSteps * sizeof(IVA_StepResults));
    for (i = 0 ; i < numSteps ; i++)
    {
        #if defined (IVA_STORE_RESULT_NAMES)
            printf(ivaData->stepResults[i].stepName, "");
        #endif
        ivaData->stepResults[i].numResults = 0;
        ivaData->stepResults[i].results = NULL;
    }

    // Create the coordinate systems
	ivaData->baseCoordinateSystems = NULL;
	ivaData->MeasurementSystems = NULL;
	if (numCoordSys)
	{
		ivaData->baseCoordinateSystems = (CoordinateSystem*)malloc(sizeof(CoordinateSystem) * numCoordSys);
		ivaData->MeasurementSystems = (CoordinateSystem*)malloc(sizeof(CoordinateSystem) * numCoordSys);
	}

    ivaData->numCoordSys = numCoordSys;

Error:
    return ivaData;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_DisposeData
//
// Description  : Releases the memory allocated in the IVA_Data structure
//
// Parameters   : ivaData  -  Internal data structure
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
int ImageProcessor::IVA_DisposeData(IVA_Data* ivaData)
{
    int i;


    // Releases the memory allocated for the image buffers.
    for (i = 0 ; i < IVA_MAX_BUFFERS ; i++)
        imaqDispose(ivaData->buffers[i]);

    // Releases the memory allocated for the array of measurements.
    for (i = 0 ; i < ivaData->numSteps ; i++)
        IVA_DisposeStepResults(ivaData, i);

    free(ivaData->stepResults);

    // Dispose of coordinate systems
    if (ivaData->numCoordSys)
    {
        free(ivaData->baseCoordinateSystems);
        free(ivaData->MeasurementSystems);
    }

    free(ivaData);

    return TRUE;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function Name: IVA_DisposeStepResults
//
// Description  : Dispose of the results of a specific step.
//
// Parameters   : ivaData    -  Internal data structure
//                stepIndex  -  step index
//
// Return Value : success
//
////////////////////////////////////////////////////////////////////////////////
 int ImageProcessor::IVA_DisposeStepResults(IVA_Data* ivaData, int stepIndex)
{
    int i;

    
    for (i = 0 ; i < ivaData->stepResults[stepIndex].numResults ; i++)
    {
        if (ivaData->stepResults[stepIndex].results[i].type == IVA_STRING)
            free(ivaData->stepResults[stepIndex].results[i].resultVal.strVal);
			//if(ivaData->stepResults[stepIndex].results[i].type == NULL){
				//printf("Results Disposed\n");
			//}
    }

    free(ivaData->stepResults[stepIndex].results);

    return TRUE;
}


