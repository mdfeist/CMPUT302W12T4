/**
 * Util.h
 *
 * Common helper functions.
 * Created By: Michael Feist
 */

#include <Windows.h>
#include <string.h>
#include <iostream>

namespace Util
{
	std::string openfilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
	void getDesktopResolution(int& horizontal, int& vertical);
};
