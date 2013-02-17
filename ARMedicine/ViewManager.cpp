#include "ViewManager.h"


bool ViewManager::addView(std::string key, View* v)
{
	std::pair<std::map<std::string, View*>::iterator,bool> ret;
	ret = _views.insert ( std::pair<std::string, View*>(key, v) );

	if (ret.second == false)
		return false;

	return true;
}

View* ViewManager::getView(std::string key)
{
	std::map<std::string, View*>::iterator ret;
	ret = _views.find(key);

	if ( ret == _views.end())
		return 0;

	return ret->second;
}

bool ViewManager::removeView(std::string key)
{
	std::map<std::string, View*>::iterator ret;
	ret = _views.find(key);

	if ( ret == _views.end())
		return false;

	_views.erase(ret);

	return true;
}

bool ViewManager::changeToView(std::string key)
{
	std::map<std::string, View*>::iterator ret;
	ret = _views.find(key);

	if ( ret == _views.end())
		return false;

	((View*)ret->second)->show();

	if (currentView)
		currentView->show();

	currentView = (View*)ret->second;

	return true;
}