// xboxcontrollerhandler.cpp : Defines the entry point for the console application.
//

// http://www.david-amador.com/2012/04/xbox-360-controller-input-in-c-via-xinput/
// http://programming4.us/multimedia/3932.aspx
// http://forums.dashhacks.com/xbox360-tutorials-guides/287286-using-xinput-xbox-360-controller-support.html


#include <Windows.h>

#include <XInput.h>
#include <stdio.h>
#include "xboxcontrollerhandler.h"

#pragma comment(lib, "XInput.lib")


int handleController(void)
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

			setButtonFunction(&(xControl.aButton), printSomethingElse);

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
		button->arg();
		button->isPressed = true;
	}
	else if(!(condition)){
		button->isPressed = false;
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
	xControl.dUpButton.arg =  printButtonStuff;
	xControl.dDownButton.arg =  printButtonStuff;
	xControl.dLeftButton.arg =  printButtonStuff;
	xControl.dRightButton.arg =  printButtonStuff;
	xControl.startButton.arg =  printButtonStuff;
	xControl.backButton.arg =  printButtonStuff;
	xControl.leftThumb.arg =  printButtonStuff;
	xControl.rightThumb.arg =  printButtonStuff;
	xControl.leftShoulder.arg =  printButtonStuff;
	xControl.rightShoulder.arg =  printButtonStuff;
	xControl.aButton.arg =  printButtonStuff;
	xControl.bButton.arg =  printButtonStuff;
	xControl.xButton.arg =  printButtonStuff;
	xControl.yButton.arg =  printButtonStuff;

	xControl.leftStick.moveLeft.arg = printSomethingElse;
	xControl.leftStick.moveRight.arg = printButtonStuff;
	xControl.leftStick.moveUp.arg = printSomethingElse;
	xControl.leftStick.moveDown.arg = printButtonStuff;

	xControl.rightStick.moveLeft.arg = printSomethingElse;
	xControl.rightStick.moveRight.arg = printButtonStuff;
	xControl.rightStick.moveUp.arg = printSomethingElse;
	xControl.rightStick.moveDown.arg = printButtonStuff;

	xControl.leftTrigger.pressed.arg = printSomethingElse;
	xControl.rightTrigger.pressed.arg = printButtonStuff;

	return 0;
}