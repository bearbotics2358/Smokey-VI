#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <nivision.h>
#include <WPILib.h>
//#include <nimachinevision.h>

#define IVA_MAX_BUFFERS 10
#define IVA_STORE_RESULT_NAMES //If you want to get the name of result, we don't need it

#define VisionErrChk(Function) {if (!(Function)) {success = 0; goto Error;}}

typedef enum IVA_ResultType_Enum {
	IVA_NUMERIC, 
	IVA_BOOLEAN, 
	IVA_STRING
} IVA_ResultType;

typedef union IVA_ResultValue_Struct{    // A result in Vision Assistant can be of type double, BOOL or string.
    double numVal;
    bool   boolVal;
    char*  strVal;
} IVA_ResultValue;

typedef struct IVA_Result_Struct
{
#if defined (IVA_STORE_RESULT_NAMES)
    char resultName[256];           // Result name
#endif
    IVA_ResultType  type;           // Result type
    IVA_ResultValue resultVal;      // Result value
} IVA_Result;

typedef struct IVA_StepResultsStruct
{
#if defined (IVA_STORE_RESULT_NAMES)
    char stepName[256];             // Step name
#endif
    int         numResults;         // number of results created by the step
    IVA_Result* results;            // array of results
} IVA_StepResults;

typedef struct IVA_Data_Struct
{
    Image* buffers[IVA_MAX_BUFFERS];            // Vision Assistant Image Buffers
    IVA_StepResults* stepResults;              // Array of step results
    int numSteps;                               // Number of steps allocated in the stepResults array
    CoordinateSystem *baseCoordinateSystems;    // Base Coordinate Systems
    CoordinateSystem *MeasurementSystems;       // Measurement Coordinate Systems
    int numCoordSys;                            // Number of coordinate systems
} IVA_Data;

class ImageProcessor{
	private:
		
		AxisCamera *ap_camera;
		const char *IP;	
		bool a_verbose;
		
		//functions
		
		 IVA_Data* IVA_InitData(int numSteps, 
									int numCoordSys);
		
	static	 int IVA_DisposeData(IVA_Data* ivaData);
		
		static int IVA_DisposeStepResults(IVA_Data* ivaData,
									int stepIndex);
		
	static	 int IVA_CLRThreshold(Image* image, 
									int min1, 
									int max1, 
									int min2, 
									int max2, 
									int min3, 
									int max3,
									int colorMode);
		
	static	 int IVA_MatchShape(Image* image,
									char* templatePath,
									double minimumScore,
									int scaleInvariance,
									IVA_Data* ivaData,
									int stepIndex);
		
		
		
	public:
		~ImageProcessor();
		ImageProcessor(bool verbose);
		
		int IVA_ProcessImage(Image *image);
		int getRectangles();
		
		
		//int[] *x;
		//int[] *y;
};


#endif //IMAGEPROCESSOR_H
