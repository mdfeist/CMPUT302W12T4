/**
 * Main
 * Created By: Michael Feist
 */

#include "Application.h"

#include <Windows.h>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	return Application::run();
}