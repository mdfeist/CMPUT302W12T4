
namespace GenericInput{
	//Get methods
	float getFOV();
	float getAspect();
	float getCameraOffsetX();
	float getCameraOffsetY();
	float getCameraOffsetZ();

	//Set methods
	int setFOV(float f);
	int setAspect(float a);
	int setCameraOffsetX(float v);
	int setCameraOffsetY(float v);
	int setCameraOffsetZ(float v);

	//Increase methods
	int increaseFOV(float f);
	int increaseAspect(float a);
	int increaseCameraOffsetX(float v);
	int increaseCameraOffsetY(float v);
	int increaseCameraOffsetZ(float v);
}