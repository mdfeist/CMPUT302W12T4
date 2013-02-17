#pragma once

#include "View.h"
#include "UIButton.h"

#include <osgWidget/box>

class UITabBar : public View
{
private:
	osgWidget::Box* menuBar;

public:
	UITabBar(osgWidget::WindowManager* wm);
	
	UIButton* createButton(const std::string& label, osgWidget::Callback* cb = 0);
	void addButton(UIButton* button);

	virtual bool show();
	virtual bool hide();
};

