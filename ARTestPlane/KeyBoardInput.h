/**
 * KeyBoardInput.h
 * Created By: Michael Feist
 */

#include <osgGA/GUIEventHandler>

class KeyBoardInput : public osgGA::GUIEventHandler
{
private:
	float fov;
	float aspect;
public:
	float x, y, z;

	float getFOV() { return fov; }
	void setFOV(float f) { fov = f; }

	float getAspect() { return aspect; }
	void setAspect(float a) { aspect = a; }

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
	virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };
};