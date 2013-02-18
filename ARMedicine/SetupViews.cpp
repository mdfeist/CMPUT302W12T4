#include "SetupViews.h"
#include "TitleView.h"

#include "UIButton.h"
#include "UITabBar.h"

#include <osgWidget/ViewerEventHandlers>

TitleView* titleBar;
UITabBar* menuBar;

void SetupViews::init(osgWidget::WindowManager* wm)
{ 
	// Title Bar
	titleBar = new TitleView("ARMedicine", wm);

	menuBar = new UITabBar(wm);

	// Menu Button
	UIButton* button = new UIButton("Menu");
	button->setPadLeft(10);
	button->setPadRight(5);
	button->setPadBottom(10);

	// 3D Model Button
	UIButton* button2 = new UIButton("3D Model");
	button2->setPadBottom(10);

	menuBar->addButton(button);
	menuBar->addButton(button2);
}

void SetupViews::showTitle()
{
	titleBar->show();
}

void SetupViews::hideTitle()
{
	titleBar->hide();
}

void SetupViews::showMenu()
{
	menuBar->show();
}

void SetupViews::hideMenu()
{
	menuBar->hide();
}