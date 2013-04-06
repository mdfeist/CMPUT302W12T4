/**
 * XBoxInput.cpp
 * Created By: Devon Waldon
 */

#include "GenericInput.h"
#include "XBoxInput.h"
#include "xboxcontrollerhandler.h"
#include <stdio.h>

float stickReduction = 1000000.f;

/**
 * Menu setups for calibration via the XBox controller.
 */
int XBoxInput::setMenuNormal(){
	printf("\n\nMenu: Normal");
	printf("\n\tStart Button: enter menu selection.");
	setupButtons();

	return 0;
}

int XBoxInput::setMenuSelect(){
	printf("\n\nMenu: Select");
	printf("\n\tStart Button: enter menu selection.");
	printf("\n\tA Button: enter camera adjustment menu.");
	printf("\n\tX Button: enter model adjustment menu.");
	printf("\n\tY Button: enter save menu.");
	printf("\n\tB Button: exit and return to normal menu.");
	setupButtons();

	xControl.bButton.arg = XBoxInput::setMenuNormal;
	xControl.aButton.arg = XBoxInput::setMenuCamera;
	xControl.xButton.arg = XBoxInput::setMenuModel;
	xControl.yButton.arg = XBoxInput::setMenuSave;

	return 0;
}

int XBoxInput::setMenuCamera(){
	printf("\n\nMenu: Camera");
	printf("\n\tStart Button: enter menu selection.");
	printf("\n\tLeft Stick Left/Right: +/- camera offset in X plane.");
	printf("\n\tLeft Stick Up/Down: +/- camera offset in Y plane.");
	printf("\n\tRight Stick Left/Right: +/- camera offset in Z plane.");
	printf("\n\tD-Pad Up/Down: +/- camera field of view.");
	printf("\n\tD-Pad Left/Right: +/- camera aspect ratio.");
	setupButtons();
	
	xControl.leftStick.moveH = XBoxInput::modifyCameraOffsetX;
	xControl.leftStick.moveV = XBoxInput::modifyCameraOffsetY;
	xControl.rightStick.moveH = XBoxInput::modifyCameraOffsetZ;

	xControl.dUpButton.arg = XBoxInput::increaseFOV;
	xControl.dDownButton.arg = XBoxInput::decreaseFOV;
	xControl.dLeftButton.arg = XBoxInput::increaseAspect;
	xControl.dRightButton.arg = XBoxInput::decreaseAspect;

	return 0;
}

int XBoxInput::setMenuModel(){
	printf("\n\nMenu: Model");
	setupButtons();

	return 0;
}

int XBoxInput::setMenuSave(){
	printf("\n\nMenu: Save");
	setupButtons();

	return 0;
}

/**
 * Wrapper methods to interface between the single-argument 
 * xboxcontrollerhandler button functions and the potentially multi-argument
 * GenericInput functions.
 */
int XBoxInput::modifyCameraOffsetX(){	
	float increase = (float)xControl.leftStick.xValue/(32768.f*stickReduction);
	GenericInput::increaseCameraOffsetX(increase);

	return 0;
}

int XBoxInput::modifyCameraOffsetY(){	
	float increase = (float)xControl.leftStick.yValue/(32768.f*stickReduction);
	GenericInput::increaseCameraOffsetY(increase);

	return 0;
}

int XBoxInput::modifyCameraOffsetZ(){	
	float increase = (float)xControl.rightStick.xValue/(32768.f*stickReduction);
	GenericInput::increaseCameraOffsetZ(increase);

	return 0;
}

int XBoxInput::increaseFOV(){
	GenericInput::increaseFOV(0.1f);

	return 0;
}

int XBoxInput::decreaseFOV(){
	GenericInput::increaseFOV(-0.1f);
	
	return 0;
}

int XBoxInput::increaseAspect(){
	GenericInput::increaseAspect(0.1f);
	
	return 0;
}

int XBoxInput::decreaseAspect(){
	GenericInput::increaseAspect(-0.1f);
	
	return 0;
}