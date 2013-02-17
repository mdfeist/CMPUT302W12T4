#include "MenuView.h"
#include "TitleView.h"

#include "Util.h"
#include "UIButton.h"
#include "UITabBar.h"

#include <osgWidget/ViewerEventHandlers>

TitleView* titleBar;
UITabBar* menuBar;

int width, height;

void MenuView::init(osgWidget::WindowManager* wm)
{
	Util::getDesktopResolution(width, height);

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

void MenuView::showTitle()
{
	titleBar->show();
}

void MenuView::hideTitle()
{
	titleBar->hide();
}

void MenuView::showMenu()
{
	menuBar->show();
}

void MenuView::hideMenu()
{
	menuBar->hide();
}