/**
 * MenuView.h
 * Created By: Michael Feist
 */

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <osgWidget/WindowManager>

namespace MenuView {

	void init(osgWidget::WindowManager* wm);
	void showTitle();
	void hideTitle();
	void showMenu();
	void hideMenu();

};

#endif // MENUVIEW_H