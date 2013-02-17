#pragma once

#include "Singleton.h"

#include "View.h"

#include <map>
#include <string>

class ViewManager : public Singleton<ViewManager>
{
private:
	std::map<std::string, View*> _views;
	View* currentView;
public:

	bool addView(std::string key, View* v);
	View* getView(std::string key);
	bool removeView(std::string key);

	bool changeToView(std::string key);
};

