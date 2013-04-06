#include "GenericInput.h"
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