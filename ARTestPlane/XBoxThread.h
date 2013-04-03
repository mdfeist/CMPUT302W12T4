/**
 * XBoxThread.h
 * Created By: Devon Waldon
 */

#ifndef XBOXTHREAD_H
#define XBOXTHREAD_H

#include "xboxcontrollerhandler.h"

namespace XBoxThread {

	#define X_BUTTON &(xControl.xButton)
	//add all

	int startThread();

};

#endif // XBOXTHREAD_H

//create deadzone set/get
//have joystick functions