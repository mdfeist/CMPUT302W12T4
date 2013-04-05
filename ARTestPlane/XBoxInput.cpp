/**
 * XBoxInput.cpp
 * Created By: Devon Waldon
 */

#include "GenericInput.h"
#include "XBoxInput.h"
#include "xboxcontrollerhandler.h"
#include <stdio.h>

int XBoxInput::modifyCameraOffsetX(){	
	GenericInput::increaseCameraOffsetX((float)xControl.leftStick.xValue/32728.f);
	return 0;
}

int XBoxInput::modifyCameraOffsetY(){	
	GenericInput::increaseCameraOffsetY((float)(xControl.leftStick.yValue)/32768.f);
	return 0;
}

int XBoxInput::modifyCameraOffsetZ(){	
	GenericInput::increaseCameraOffsetZ((float)(xControl.rightStick.xValue)/32768.f);
	return 0;
}