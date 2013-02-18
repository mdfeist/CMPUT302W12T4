/**
 * SetupViews.h
 * Created By: Michael Feist
 */

#ifndef SETUPVIEWS_H
#define SETUPVIEWS_H

#include <osgWidget/WindowManager>

namespace SetupViews {

	void init(osgWidget::WindowManager* wm);
	void showTitle();
	void hideTitle();
	void showMenu();
	void hideMenu();

};

#endif // SETUPVIEWS_H