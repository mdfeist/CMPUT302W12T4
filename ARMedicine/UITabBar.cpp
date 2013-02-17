#include "UITabBar.h"

#include <osgWidget/ViewerEventHandlers>

UITabBar::UITabBar(osgWidget::WindowManager* wm)
{
	menuBar = new osgWidget::Box(std::string("Menu Bar"),
			osgWidget::Box::HORIZONTAL,
            true);
	
	menuBar->getBackground()->setColor(0, 0, 0, 0);

	wm->addChild(menuBar);
}

UIButton* UITabBar::createButton(const std::string& label, osgWidget::Callback* cb)
{
	UIButton* button = new UIButton(label);

	if (cb)
	{
		button->addCallback(cb);
	}

	menuBar->addWidget(button);

	return button;
}

void UITabBar::addButton(UIButton* button)
{
	menuBar->addWidget(button);
}

bool UITabBar::show()
{
	return menuBar->show();
}

bool UITabBar::hide()
{
	return menuBar->hide();
}