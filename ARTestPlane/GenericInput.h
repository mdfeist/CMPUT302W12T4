
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
	float getModelScale(int rigidBody);
	int getModelFlipX(int rigidBody);
	int getModelFlipY(int rigidBody);
	int getModelFlipZ(int rigidBody);

	//Set methods
	int setFOV(float f);
	int setAspect(float a);
	int setCameraOffsetX(float v);
	int setCameraOffsetY(float v);
	int setCameraOffsetZ(float v);
	int setModelRotationX(int rigidBody, float degrees);
	int setModelRotationY(int rigidBody, float degrees);
	int setModelRotationZ(int rigidBody, float degrees);
	int setModelScale(int rigidBody, float scale);
	//Not REALLY set methods... they invert the 'flip_' integer, 'flipping' the
	//model.
	int modelFlipX(int rigidBody);
	int modelFlipY(int rigidBody);
	int modelFlipZ(int rigidBody);

	//Increase methods
	int increaseFOV(float f);
	int increaseAspect(float a);
	int increaseCameraOffsetX(float v);
	int increaseCameraOffsetY(float v);
	int increaseCameraOffsetZ(float v);
	int increaseModelRotationX(int rigidBody, float degrees);
	int increaseModelRotationY(int rigidBody, float degrees);
	int increaseModelRotationZ(int rigidBody, float degrees);
	int increaseModelScale(int rigidBody, float scale);
}