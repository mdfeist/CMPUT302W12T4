#pragma once

#include <osgWidget/Box>
#include <osgWidget/Canvas>

class TabBar : public osgWidget::Box
{
private:
	osg::ref_ptr<osgWidget::Box>    _tabs;
    osg::ref_ptr<osgWidget::Canvas> _windows;

	bool callbackTabPressed(osgWidget::Event& ev);

public:
	TabBar(const std::string& name);
	~TabBar(void);
};

