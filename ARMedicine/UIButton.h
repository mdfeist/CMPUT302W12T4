#pragma once

#include <osgWidget/Label>

class UIButton: public osgWidget::Label {
private:
	osg::Vec4 backGroundColor;
public:
    UIButton(const std::string& label);

    // NOTE! I need to make it clearer than Push/Release can happen so fast that
    // the changes you make aren't visible with your refresh rate. Throttling state
    // changes and what-have-you on mousePush/mouseRelease/etc. is going to be
    // annoying...

	virtual bool mouseOver(osgWidget::Event& ev) {
        setColor(backGroundColor + osg::Vec4(0.1f, 0.1f, 0.1f, 0.0f));
        
        return true;
    }

	virtual bool mouseLeave(osgWidget::Event& ev) {
        setColor(backGroundColor);
        
        return true;
    }

    virtual bool mousePush(osgWidget::Event& ev) {
        setColor(backGroundColor - osg::Vec4(0.1f, 0.1f, 0.1f, 0.0f));
        
        return true;
    }

    virtual bool mouseRelease(osgWidget::Event& ev) {
        setColor(backGroundColor);
        
        return true;
    }
};

