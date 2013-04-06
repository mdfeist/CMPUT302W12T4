
namespace GenericInput{

	//Camera
	void printCameraInfo();
	void saveCameraInfo();

	//Get methods
	float getFOV();
	float getAspect();
	float getCameraOffsetX();
	float getCameraOffsetY();
	float getCameraOffsetZ();
	float getModelRotationX(int rigidBody);
	float getModelRotationY(int rigidBody);
	float getModelRotationZ(int rigidBody);

	//Set methods
	int setFOV(float f);
	int setAspect(float a);
	int setCameraOffsetX(float v);
	int setCameraOffsetY(float v);
	int setCameraOffsetZ(float v);
	int setModelRotationX(int rigidBody, float degrees);
	int setModelRotationY(int rigidBody, float degrees);
	int setModelRotationZ(int rigidBody, float degrees);

	//Increase methods
	int increaseFOV(float f);
	int increaseAspect(float a);
	int increaseCameraOffsetX(float v);
	int increaseCameraOffsetY(float v);
	int increaseCameraOffsetZ(float v);
	int increaseModelRotationX(int rigidBody, float degrees);
	int increaseModelRotationY(int rigidBody, float degrees);
	int increaseModelRotationZ(int rigidBody, float degrees);

	//Helper methods
	int getModelPosition(int rigidBody);
}