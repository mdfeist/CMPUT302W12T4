/**
 * Util.cpp
 *
 * Common helper functions.
 * Created By: Michael Feist
 */

#include "Util.h"

using namespace std;

// Returns an empty string if dialog is canceled
string Util::openfilename(char *filter, HWND owner)
{
	OPENFILENAME ofn;

	char fileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	string fileNameStr;

	if ( GetOpenFileName(&ofn) )
		fileNameStr = fileName;

	return fileNameStr;
}

// Get the horizontal and vertical screen sizes in pixel
void Util::getDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}