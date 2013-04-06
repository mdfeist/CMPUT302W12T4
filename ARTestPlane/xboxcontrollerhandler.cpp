// xboxcontrollerhandler.cpp : Defines the entry point for the console application.
//

// http://www.david-amador.com/2012/04/xbox-360-controller-input-in-c-via-xinput/
// http://programming4.us/multimedia/3932.aspx
// http://forums.dashhacks.com/xbox360-tutorials-guides/287286-using-xinput-xbox-360-controller-support.html


#include <stdio.h>
#include "xboxcontrollerhandler.h"
#include "XBoxInput.h"
#include <math.h>

#pragma comment(lib, "XInput.lib")

XINPUT_STATE state;
XController xControl;

DWORD WINAPI handleController(LPVOID lpParam)
{
	/*
	 * Clears the memory of the XINPUT state object and the local XController
	 * object.
	 */
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&xControl, sizeof(XController));

	/*
	 * Sets up the button with default values.
	 */
	setupButtons();

	do{
		/*
		 *Checks if the controller is connected, and if so, monitors the state of
		 *the buttons.
		 */
		DWORD c0Connected;
		c0Connected = XInputGetState(0, &state);

		if(c0Connected == ERROR_SUCCESS){
			checkEvents();
		}
		else
			printf("\rController disconnected. Pease reconnect.\t");
	}
	while (true);

	return 0;
}

/**
  *Placeholder functions that simply display text to the terminal.
  */
int printButtonStuff(){
	printf("Button Press!\n");
	return 0;
}

int printSomethingElse(){
	printf("Oooh! Different!\n");
	return 0;
}

/**
  * Provides a single method to check all events (Hardware and Soft-buttons) to
  * simplify external use.
  */
int checkEvents(){
	/*
	 *Checks the hardware buttons
	 */
	checkButtonPress(&(xControl.leftShoulder));
	checkButtonPress(&(xControl.rightShoulder));

	checkButtonPress(&(xControl.startButton));
	checkButtonPress(&(xControl.backButton));

	checkButtonPress(&(xControl.aButton));
	checkButtonPress(&(xControl.bButton));
	checkButtonPress(&(xControl.xButton));
	checkButtonPress(&(xControl.yButton));

	checkButtonPress(&(xControl.dUpButton));
	checkButtonPress(&(xControl.dDownButton));
	checkButtonPress(&(xControl.dLeftButton));
	checkButtonPress(&(xControl.dRightButton));

	checkButtonPress(&(xControl.leftThumb));
	checkButtonPress(&(xControl.rightThumb));

	/*
	 *Checks the analog sticks
	 */
	xControl.leftStick.xValue = state.Gamepad.sThumbLX;
	xControl.leftStick.yValue = state.Gamepad.sThumbLY;
	checkStickMove(&(xControl.leftStick), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	checkButtonPress(&(xControl.leftStick.moveLeft), 
		state.Gamepad.sThumbLX < (-32768+XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.leftStick.moveRight), 
		state.Gamepad.sThumbLX > (32768-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.leftStick.moveUp), 
		state.Gamepad.sThumbLY > (32768-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.leftStick.moveDown), 
		state.Gamepad.sThumbLY < (-32768+XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));

	xControl.rightStick.xValue = state.Gamepad.sThumbRX;
	xControl.rightStick.yValue = state.Gamepad.sThumbRY;
	checkStickMove(&(xControl.rightStick), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
	checkButtonPress(&(xControl.rightStick.moveLeft), 
		state.Gamepad.sThumbRX < (-32768+XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.rightStick.moveRight), 
		state.Gamepad.sThumbRX > (32768-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.rightStick.moveUp), 
		state.Gamepad.sThumbRY > (32768-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	checkButtonPress(&(xControl.rightStick.moveDown), 
		state.Gamepad.sThumbRY < (-32768+XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));

	/*
	 *Checks the triggers
	 */
	xControl.leftTrigger.amtPressed = state.Gamepad.bLeftTrigger;
	xControl.rightTrigger.amtPressed = state.Gamepad.bRightTrigger;
	checkButtonPress(&(xControl.leftTrigger.pressed), 
		state.Gamepad.bLeftTrigger > (256-XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
	checkButtonPress(&(xControl.rightTrigger.pressed), 
		state.Gamepad.bRightTrigger > (256-XINPUT_GAMEPAD_TRIGGER_THRESHOLD));

	return 0;
}

/**
  * Checks if a button has been pressed (according to a given condition), and if 
  * so, it executes the function associated with that button.
  * 
  * Includes a default option that assumes the button is a hardware button such as
  * the 'A Button', as opposed to a 'soft' button, such as the 'Analog Stick moved
  * Left' event.
  */
int checkButtonPress(xBoxButton* button){
	return checkButtonPress(button, (state.Gamepad.wButtons & button->address)!=0);
}

int checkButtonPress(xBoxButton* button, bool condition){
	if((condition) & (!(button->isPressed))){
		if((button->arg)!=0){
			button->arg();
		}
		button->isPressed = true;
	}
	else if(!(condition)){
		button->isPressed = false;
	}

	return 0;
}

int checkStickMove(xBoxStick* stick, int threshold){
	if(abs(stick->xValue)>threshold && (stick->moveH)!=0){
		stick->moveH();
	}
	if(abs(stick->yValue)>threshold && (stick->moveV)!=0){
		stick->moveV();
	}
	return 0;
}

/**
  * Sets the function to be called when a given button is pressed.
  */
int setButtonFunction(xBoxButton* button, int (*arg)(void)){
	button->arg = arg;	
	return 0;
}

int setStickFunction(xBoxStick* stick, int (*moveH)(void), int (*moveV)(void)){
	stick->moveH = moveH;
	stick->moveV = moveV;

	return 0;
}
/**
  * Sets up the local XController object with default functions for all the
  * buttons, and proper addresses as per XINPUT.
  */
int setupButtons(){
	/*
	 * Default button addresses from XInput.h
	 * DO NOT CHANGE.
	 */
	xControl.dUpButton.address =  XINPUT_GAMEPAD_DPAD_UP;
	xControl.dDownButton.address =  XINPUT_GAMEPAD_DPAD_DOWN;
	xControl.dLeftButton.address =  XINPUT_GAMEPAD_DPAD_LEFT;
	xControl.dRightButton.address =  XINPUT_GAMEPAD_DPAD_RIGHT;
	xControl.startButton.address =  XINPUT_GAMEPAD_START;
	xControl.backButton.address =  XINPUT_GAMEPAD_BACK;
	xControl.leftThumb.address =  XINPUT_GAMEPAD_LEFT_THUMB;
	xControl.rightThumb.address =  XINPUT_GAMEPAD_RIGHT_THUMB;
	xControl.leftShoulder.address =  XINPUT_GAMEPAD_LEFT_SHOULDER;
	xControl.rightShoulder.address =  XINPUT_GAMEPAD_RIGHT_SHOULDER;
	xControl.aButton.address =  XINPUT_GAMEPAD_A;
	xControl.bButton.address =  XINPUT_GAMEPAD_B;
	xControl.xButton.address =  XINPUT_GAMEPAD_X;
	xControl.yButton.address =  XINPUT_GAMEPAD_Y;

	/*
	 * Default functions for each button, to be used for testing only.
	 * Code-specific modifications should be done by the 'setButtonFunction' method.
	 */
	xControl.dUpButton.arg =  0;
	xControl.dDownButton.arg =  0;
	xControl.dLeftButton.arg =  0;
	xControl.dRightButton.arg =  0;

	xControl.startButton.arg =  XBoxInput::setMenuSelect;
	xControl.backButton.arg =  0;
	
	xControl.leftThumb.arg =  0;
	xControl.rightThumb.arg =  0;
	
	xControl.leftShoulder.arg =  0;
	xControl.rightShoulder.arg =  0;
	
	xControl.aButton.arg =  0;
	xControl.bButton.arg =  0;
	xControl.xButton.arg =  0;
	xControl.yButton.arg =  0;

	xControl.leftStick.moveH = 0;
	xControl.leftStick.moveV = 0;
	xControl.leftStick.moveLeft.arg = 0;
	xControl.leftStick.moveRight.arg = 0;
	xControl.leftStick.moveUp.arg = 0;
	xControl.leftStick.moveDown.arg = 0;

	xControl.rightStick.moveH = 0;
	xControl.rightStick.moveV = 0;
	xControl.rightStick.moveLeft.arg = 0;
	xControl.rightStick.moveRight.arg = 0;
	xControl.rightStick.moveUp.arg = 0;
	xControl.rightStick.moveDown.arg = 0;

	xControl.leftTrigger.pressed.arg = 0;
	xControl.rightTrigger.pressed.arg = 0;

	return 0;
}