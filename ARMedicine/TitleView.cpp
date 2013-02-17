#include "TitleView.h"

#include <osgWidget/Label>
#include <osgWidget/ViewerEventHandlers>

TitleView::TitleView(const std::string& titleLabel, osgWidget::WindowManager* wm)
{
	int width = wm->getWidth();
	int height = wm->getHeight();

	// Title Bar
	titleBar = new osgWidget::Box(std::string("Title Bar"),
		osgWidget::Box::HORIZONTAL,
            true);

	titleBar->getBackground()->setColor(0.3f,0.57f,1.0f,1.0f);
	titleBar->setPosition(0, height - 100.f, 0);

	// Title
	osgWidget::Label* title = new osgWidget::Label("title", titleLabel);
	title->setFont("fonts/seguisb.ttf");
	title->setFontSize(42);
	title->setColor(0.3f,0.57f,1.0f,1.0f);
	title->setCanFill(true);

	title->setPadding(20.f);
	title->setPadRight(width - 250.f - title->getWidth());
	
	titleBar->addWidget(title);

	wm->addChild(titleBar);
}

bool TitleView::show()
{
	return titleBar->show();
}

bool TitleView::hide()
{
	return titleBar->hide();
}