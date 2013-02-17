#include "TabBar.h"

#include <osgWidget/Label>
#include <osgWidget/ViewerEventHandlers>

TabBar::TabBar(const std::string& name):
osgWidget::Box(name, osgWidget::Box::VERTICAL)
{
	_tabs    = new osgWidget::Box("tabs", osgWidget::Box::HORIZONTAL);
	_windows = new osgWidget::Canvas("canvas");

	for(unsigned int i = 0; i < 10; i++) {
		std::stringstream ss;

		// Setup everything for our Tab...
		ss << "Tab_" << i;

		osgWidget::Label* label1 = new osgWidget::Label(ss.str());

		label1->setFont("fonts/segoeui.ttf");
		label1->setFontSize(20);
		label1->setFontColor(1.0f, 1.0f, 1.0f, 1.0f);
		label1->setColor(0.0f, i / 4.0f, 0.3f, 1.0f);
		label1->setLabel(ss.str());
		label1->addSize(20.0f, 20.0f);
		label1->setShadow(0.1f);
		label1->setCanFill(true);

		_tabs->addWidget(label1);

		// Setup everything for the Window corresponding to the Tab
		// in the Canvas down below.
		std::stringstream descr;

		descr
			<< "This is some text" << std::endl
			<< "for the Tab_" << i << " tab." << std::endl
			<< "Press the button up top" << std::endl
			<< "And this should go to the next Window!" << std::endl
			;

		osgWidget::Label* label2 = new osgWidget::Label(ss.str());

		label2->setFont("fonts/segoeui.ttf");
		label2->setFontSize(15);
		label2->setFontColor(1.0f, 1.0f, 1.0f, 1.0f);
		label2->setColor(0.0f, i / 4.0f, 0.3f, 1.0f);
		label2->setLabel(descr.str());
		label2->setLayer(osgWidget::Widget::LAYER_MIDDLE, i * 2);
		label2->addSize(50.0f, 100.0f);

		_windows->addWidget(label2, 0.0f, 0.0f);

		label1->setEventMask(osgWidget::EVENT_MOUSE_PUSH);
		label1->addCallback(new osgWidget::Callback(
			&TabBar::callbackTabPressed,
			this,
			osgWidget::EVENT_MOUSE_PUSH
			));
	}

	addWidget(_tabs->embed());
	addWidget(_windows->embed());
}


TabBar::~TabBar(void)
{
}

// NOTE: This whole thing is just a hack to demonstrate a concept. The real
// implementation would need to be much cleaner.
bool TabBar::callbackTabPressed(osgWidget::Event& ev) {
	osgWidget::Canvas::Vector& objs = _windows->getObjects();

	for(unsigned int i = 0; i < objs.size(); i++) objs[i]->setLayer(
		osgWidget::Widget::LAYER_MIDDLE,
		i * 2
		);

	_windows->getByName(ev.getWidget()->getName())->setLayer(
		osgWidget::Widget::LAYER_MIDDLE,
		objs.size() * 2
		);

	_windows->resize();

	return true;
}
