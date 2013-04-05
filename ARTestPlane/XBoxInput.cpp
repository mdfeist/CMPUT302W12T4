/**
 * XBoxInput.cpp
 * Created By: Devon Waldon
 */

#include "GenericInput.h"
#include "XBoxInput.h"
#include "xboxcontrollerhandler.h"
#include <stdio.h>

int XBoxInput::modifyCameraOffsetX(){	
	float increase = (float)xControl.leftStick.xValue/32768000000.f;
	GenericInput::increaseCameraOffsetX(increase);

	return 0;
}

int XBoxInput::modifyCameraOffsetY(){	
	float increase = (float)xControl.leftStick.yValue/32768000000.f;
	GenericInput::increaseCameraOffsetY(increase);

	return 0;
}

int XBoxInput::modifyCameraOffsetZ(){	
	float increase = (float)xControl.rightStick.xValue/32768000000.f;
	GenericInput::increaseCameraOffsetZ(increase);

	return 0;
}