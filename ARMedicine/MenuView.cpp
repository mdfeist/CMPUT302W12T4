#include "MenuView.h"

#include "Util.h"
#include "UIButton.h"

#include <osgWidget/Util>
#include <osgWidget/Box>
#include <osgWidget/Canvas>
#include <osgWidget/Label>
#include <osgWidget/ViewerEventHandlers>

osgWidget::Box* titleBar;
osgWidget::Box* menuBar;

int width, height;

void MenuView::init(osgWidget::WindowManager* wm)
{
	Util::getDesktopResolution(width, height);

	// Title Bar
	titleBar = new osgWidget::Box(std::string("Title Bar"),
		osgWidget::Box::HORIZONTAL,
            true);

	titleBar->getBackground()->setColor(0.3f,0.57f,1.0f,1.0f);
	titleBar->setPosition(0, height - 100.f, 0);

	// Title
	osgWidget::Label* title = new osgWidget::Label("title", "ARMedicine");
	title->setFont("fonts/seguisb.ttf");
	title->setFontSize(42);
	title->setColor(0.3f,0.57f,1.0f,1.0f);
	title->setCanFill(true);

	title->setPadding(20.f);
	title->setPadRight(width - 250.f - title->getWidth());
	
	titleBar->addWidget(title);

	wm->addChild(titleBar);

	// Menu Button
	UIButton* button = new UIButton("Menu");
	button->setPadLeft(10);
	button->setPadRight(5);
	button->setPadBottom(10);

	// 3D Model Button
	UIButton* button2 = new UIButton("3D Model");
	button2->setPadBottom(10);

	// Menu Bar
	menuBar = new osgWidget::Box(std::string("Menu Bar"),
			osgWidget::Box::HORIZONTAL,
            true);
	
	menuBar->getBackground()->setColor(0, 0, 0, 0);
	menuBar->addWidget(button);
	menuBar->addWidget(button2);

	wm->addChild(menuBar);
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