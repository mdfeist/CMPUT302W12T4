/*
Header file that handles the xbox controller specific structures and functions

Written by: Devon Waldon
*/

struct xBoxButton{
	int address;
	bool isPressed;
	int (*arg)(void);
};

struct xBoxStick{
	int xValue;
	int yValue;
	
	xBoxButton moveLeft;
	xBoxButton moveRight;
	xBoxButton moveUp;
	xBoxButton moveDown;
};

struct xBoxTrigger{
	int amtPressed;

	xBoxButton pressed;
};

struct XController{
	xBoxButton leftShoulder;
	xBoxButton rightShoulder;

	xBoxButton startButton;
	xBoxButton backButton;

	xBoxButton aButton;
	xBoxButton bButton;
	xBoxButton xButton;
	xBoxButton yButton;

	xBoxButton dUpButton;
	xBoxButton dDownButton;
	xBoxButton dLeftButton;
	xBoxButton dRightButton;

	xBoxButton leftThumb;
	xBoxButton rightThumb;

	xBoxStick leftStick;
	xBoxStick rightStick;

	xBoxTrigger leftTrigger;
	xBoxTrigger rightTrigger;
};

XINPUT_STATE state;
XController xControl;

int handleController();
int checkEvents();

int checkButtonPress(xBoxButton* button);
int checkButtonPress(xBoxButton* button, bool customCondition);
int setButtonFunction(xBoxButton* button, int (*arg)(void));
int setupButtons();

int printButtonStuff();
int printSomethingElse();
