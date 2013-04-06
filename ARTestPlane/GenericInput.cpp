#include "GenericInput.h"
#include "Settings.h"

#include <stdio.h>

float fov;
float aspect;
float cameraOffsetX, cameraOffsetY, cameraOffsetZ;

/**
 * Camera
 */
void GenericInput::printCameraInfo(){
	printf("\nCamera\n");
	printf("\tFOV: %.2f\n", fov);
	printf("\tAspect Ratio: %.2f\n", aspect);
	printf("\tOffset: %.2f, %.2f, %.2f\n", cameraOffsetX, cameraOffsetY, cameraOffsetZ);
}

void GenericInput::saveCameraInfo(){
	Settings::saveCameraInfo(fov, aspect, cameraOffsetX, cameraOffsetY, cameraOffsetZ);
	printf("\nSettings saved successfully.");
}

/**
  * 'Setter' methods for the variables.
  */
int GenericInput::setFOV(float f){
	fov = f;

	return 0;
}

int GenericInput::setAspect(float a){
	aspect = a;

	return 0;
}

int GenericInput::setCameraOffsetX(float v){
	cameraOffsetX = v;

	return 0;
}

int GenericInput::setCameraOffsetY(float v){
	cameraOffsetY = v;

	return 0;
}

int GenericInput::setCameraOffsetZ(float v){
	cameraOffsetZ = v;

	return 0;
}

int GenericInput::setModelRotationX(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationX = degrees;

	return 0;
}

int GenericInput::setModelRotationY(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationY = degrees;

	return 0;
}

int GenericInput::setModelRotationZ(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationZ = degrees;

	return 0;
}

/**
  * 'Getter' methods for the variables.
  */
float GenericInput::getFOV(){
	return fov;
}

float GenericInput::getAspect(){
	return aspect;
}

float GenericInput::getCameraOffsetX(){
	return cameraOffsetX;
}

float GenericInput::getCameraOffsetY(){
	return cameraOffsetY;
}

float GenericInput::getCameraOffsetZ(){
	return cameraOffsetZ;
}

float GenericInput::getModelRotationX(int rigidBody){
	return Settings::getModelAt(GenericInput::getModelPosition(rigidBody))->rotationX;
}

float GenericInput::getModelRotationY(int rigidBody){
	return Settings::getModelAt(GenericInput::getModelPosition(rigidBody))->rotationY;
}

float GenericInput::getModelRotationZ(int rigidBody){
	return Settings::getModelAt(GenericInput::getModelPosition(rigidBody))->rotationZ;
}

/**
  * 'Increase' methods for the variables. Allows for an increase by a given 
  * amount.
  */

int GenericInput::increaseFOV(float f){
	fov = fov + f;

	return 0;
}

int GenericInput::increaseAspect(float a){
	aspect = aspect + a;

	return 0;
}

int GenericInput::increaseCameraOffsetX(float v){
	cameraOffsetX = cameraOffsetX + v;

	return 0;
}

int GenericInput::increaseCameraOffsetY(float v){
	cameraOffsetY = cameraOffsetY + v;

	return 0;
}

int GenericInput::increaseCameraOffsetZ(float v){
	cameraOffsetZ = cameraOffsetZ + v;

	return 0;
}

int GenericInput::increaseModelRotationX(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationX = m->rotationX + degrees;

	return 0;
}

int GenericInput::increaseModelRotationY(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationY = m->rotationY + degrees;

	return 0;
}

int GenericInput::increaseModelRotationZ(int rigidBody, float degrees){
	Settings::Model3D * m = Settings::getModelAt(GenericInput::getModelPosition(rigidBody));
	m->rotationZ = m->rotationZ + degrees;

	return 0;
}


/**
 * Helper methods
 */

int GenericInput::getModelPosition(int rigidBody){
	for(int i=0;i<Settings::getNumberOfModels();i++){
		if(rigidBody==Settings::getModelAt(i)->rigidbody){
			return i;
		}
	}

	return -1;
}