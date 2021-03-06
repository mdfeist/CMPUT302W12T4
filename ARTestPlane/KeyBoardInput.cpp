/**
 * KeyBoardInput.cpp
 * Created By: Michael Feist
 */

#include "KeyBoardInput.h"
#include "GenericInput.h"

bool KeyBoardInput::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			switch(ea.getKey())
			{
			case 'r':
				if (GenericInput::getMode() == GenericInput::CALIBRATION) {
					GenericInput::setMode(GenericInput::RENDER);
					printf("\nRender Mode\n");
				} else {
					GenericInput::setMode(GenericInput::CALIBRATION);
					printf("\nCalibration Mode\n");
				}
				return false;
				break;
			case 'o':
				GenericInput::saveCameraInfo();
				return false;
				break;
			case 'p':
				GenericInput::printCameraInfo();
				return false;
				break;
			case '=':
				GenericInput::increaseFOV(0.1f);
				return false;
				break;
			case '-':
				GenericInput::increaseFOV(-0.1f);
				return false;
				break;
			case 'w':
				GenericInput::increaseAspect(0.1f);
				return false;
				break;
			case 'q':
				GenericInput::increaseAspect(-0.1f);
				return false;
				break;
			case 'z':
				GenericInput::increaseCameraOffsetX(-0.1f);
				return false;
				break;
			case 'x':
				GenericInput::increaseCameraOffsetY(-0.1f);
				return false;
				break;
			case 'c':
				GenericInput::increaseCameraOffsetZ(-0.1f);
				return false;
				break;
			case 'a':
				GenericInput::increaseCameraOffsetX(0.1f);
				return false;
				break;
			case 's':
				GenericInput::increaseCameraOffsetY(0.1f);
				return false;
				break;
			case 'd':
				GenericInput::increaseCameraOffsetZ(0.1f);
				return false;
				break;
			default:
				return false;
			} 
		}
	default:
		return false;
	}
}