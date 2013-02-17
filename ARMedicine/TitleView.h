#pragma once

#include "View.h"

#include <osgWidget/Box>

class TitleView : public View
{
private:
	osgWidget::Box* titleBar;

public:
	TitleView(const std::string& titleLabel, osgWidget::WindowManager* wm);

	virtual bool show();
	virtual bool hide();
};

