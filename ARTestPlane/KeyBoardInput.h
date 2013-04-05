/**
 * KeyBoardInput.h
 * Created By: Michael Feist
 */

#include <osgGA/GUIEventHandler>

class KeyBoardInput : public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};