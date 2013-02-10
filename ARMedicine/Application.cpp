/**
 * Application.cpp
 * Created By: Michael Feist
 */

#include "Application.h"

#include "SimpleOSGRender.h"

#include <Windows.h>
#include <stdio.h>

int Application::run()
{
	SimpleOSGRender::render();

	return 0;
}