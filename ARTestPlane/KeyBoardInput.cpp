/**
 * KeyBoardInput.cpp
 * Created By: Michael Feist
 */

#include "KeyBoardInput.h"

bool KeyBoardInput::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			switch(ea.getKey())
			{
			case '=':
				fov += 0.1f;
				return false;
				break;
			case '-':
				fov -= 0.1f;
				return false;
				break;
			case 'w':
				aspect += 0.1f;
				return false;
				break;
			case 'q':
				aspect -= 0.1f;
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