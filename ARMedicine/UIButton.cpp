#include "UIButton.h"

UIButton::UIButton(const std::string& label):
osgWidget::Label("", label) 
{
	backGroundColor = osg::Vec4(0.3f,0.57f,1.0f,1.0f);

	setFont("fonts/segoeui.ttf");
	setFontSize(30);
	setColor(backGroundColor);
	setCanFill(true);
	//setShadow(0.1f);
	setEventMask(osgWidget::EVENT_MASK_MOUSE_CLICK | osgWidget::EVENT_MASK_MOUSE_MOVE);
	//addSize(30.0f, 20.0f);
	setSize(250.0f, 75.0f);

	// Enter
	addCallback(new osgWidget::Callback(
		&UIButton::mouseOver,
		this,
		osgWidget::EVENT_MOUSE_OVER
		));

	// Leave
	addCallback(new osgWidget::Callback(
		&UIButton::mouseLeave,
		this,
		osgWidget::EVENT_MOUSE_LEAVE
		));

	// Push
	addCallback(new osgWidget::Callback(
		&UIButton::mousePush,
		this,
		osgWidget::EVENT_MOUSE_PUSH
		));

	// Release
	addCallback(new osgWidget::Callback(
		&UIButton::mouseRelease,
		this,
		osgWidget::EVENT_MOUSE_RELEASE
		));
}